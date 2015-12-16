#ifndef __EASY_H5_FILE_HPP__
#define __EASY_H5_FILE_HPP__

#include <vector>
#include <cstring>
#include <algorithm>
#include <map>
#include <iostream>

#include "hdf5.h"
#include "EasyH5Utils.hpp"

class EasyH5File {

    public:
    EasyH5File(const std::string& fname) {
        fid_ = H5Fcreate(fname.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
        auto root = H5Gopen(fid_, "/", H5P_DEFAULT);
        handles_["/"] = root;
    }

    ~EasyH5File() {
        for (auto& kv : handles_) {
            H5Gclose(kv.second);
        }
        H5Fclose(fid_);
    }
    bool getHandle(const std::string& name, hid_t& h) {
        auto hit = handles_.find(name);
        if (hit != handles_.end()) {
            h = hit->second;
            return true;
        } else {
            return false;
        }
    }

    bool addGroup(const std::string& gname) {
        auto gid = H5Gcreate(fid_, gname.c_str(), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        handles_[gname] = gid;
        return true;
    }

    /**
     * Inspired by kallisto's vector_to_h5 function
     */
    template <typename T>
    herr_t writeVectorToGroup(
            const std::vector<T>& vec,
            const std::string& groupName,
            const std::string& name,
            uint8_t compression = 6
            ) {
        using namespace easyh5::utils;
        herr_t errStatus;
        hsize_t dims[1] = {vec.size()};

        auto pid = H5Pcreate(H5P_DATASET_CREATE);
        errStatus = H5Pset_chunk(pid, 1, dims);
        // if (errorStatus < 0) { }

        errStatus = H5Pset_deflate(pid, compression);

        auto dtypeID = datatypeID(vec);
        auto dspaceID = H5Screate_simple(1, dims, nullptr);

        auto gidIt = handles_.find(groupName);
        if (gidIt == handles_.end()) {
            std::cerr << "The group [" << groupName << "] does not extst!\n";
            return -1;
        }
        auto dsetID = H5Dcreate(gidIt->second, name.c_str(), dtypeID,
                                dspaceID, H5P_DEFAULT, pid, H5P_DEFAULT);

        auto dptr = rawPtr(vec);
        errStatus = H5Dwrite(dsetID, dtypeID, H5S_ALL, H5S_ALL, H5P_DEFAULT, dptr);

        /** close necessary handles **/
        errStatus = H5Pclose(pid);
        errStatus = H5Dclose(dsetID);
        errStatus = H5Sclose(dspaceID);
        if (std::is_same<std::string, T>::value) {
            errStatus = H5Tclose(dtypeID);
            delete [] dptr;
        }

        return errStatus;
    }
private:
    hid_t fid_;
    std::map<std::string, hid_t> handles_;
};


#endif // __EASY_H5_FILE_HPP__
