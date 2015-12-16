#ifndef __EASY_H5_UTILS_HPP__
#define __EASY_H5_UTILS_HPP__

#include <vector>
#include <algorithm>
#include <cstring>
#include "hdf5.h"

namespace easyh5 {
    namespace utils {

        hid_t datatypeID(const std::vector<int64_t>& v);

        hid_t datatypeID(const std::vector<int32_t>& v);

        hid_t datatypeID(const std::vector<uint64_t>& v);

        hid_t datatypeID(const std::vector<uint32_t>& v);

        hid_t datatypeID(const std::vector<double>& v);

        hid_t datatypeID(const std::vector<std::string>& v);

        template <typename T>
        const T* rawPtr(const std::vector<T>& vec);

        char* rawPtr(const std::vector<std::string>& vec);

    }
}

#endif // __EASY_H5_UTILS_HPP__

