#include "EasyH5Utils.hpp"

namespace easyh5 {
    namespace utils {

        hid_t datatypeID(const std::vector<int64_t>& v) {
            return H5T_NATIVE_LONG;
        }

        hid_t datatypeID(const std::vector<int32_t>& v) {
            return H5T_NATIVE_INT;
        }

        hid_t datatypeID(const std::vector<uint64_t>& v) {
            return H5T_NATIVE_ULONG;
        }

        hid_t datatypeID(const std::vector<uint32_t>& v) {
            return H5T_NATIVE_UINT;
        }

        hid_t datatypeID(const std::vector<double>& v) {
            return H5T_NATIVE_DOUBLE;
        }

        hid_t datatypeID(const std::vector<std::string>& v) {
            auto lit = std::max_element(v.begin(), v.end(),
                    [](const std::string& a, const std::string& b) -> bool {
                    return a.length() < b.length();
                    }
                    );
            auto maxLen = lit->length() + 1;
            auto dtid = H5Tcopy(H5T_C_S1);
            auto errStatus = H5Tset_size(dtid, maxLen);
            return dtid;
        }

        /*
        template <class T>
            struct RawPtrReturnT {
                using type = const T*;
            };

        template<>
            struct RawPtrReturnT<std::string> {
                using type = char*;
            };
        */

        template <typename T>
        const T* rawPtr(const std::vector<T>& vec)  { return vec.data(); }

        char* rawPtr(const std::vector<std::string>& vec) {
                auto lit = std::max_element(vec.begin(), vec.end(),
                        [](const std::string& a, const std::string& b) -> bool {
                        return a.length() < b.length();
                        }
                        );
                auto maxLen = lit->length() + 1;
                char* buf = new char[maxLen * vec.size()];
                char* start = buf;

                for (const auto& s : vec) {
                    std::strcpy(start, s.c_str());
                    start += maxLen;
                }

                return buf;
            }

        template const int32_t* rawPtr<int32_t>(const std::vector<int32_t>& vec);

        template const int64_t* rawPtr<int64_t>(const std::vector<int64_t>& vec);

        template const uint32_t* rawPtr<uint32_t>(const std::vector<uint32_t>& vec);

        template const uint64_t* rawPtr<uint64_t>(const std::vector<uint64_t>& vec);

        template const double* rawPtr<double>(const std::vector<double>& vec);

        template const float* rawPtr<float>(const std::vector<float>& vec);

    }
}
