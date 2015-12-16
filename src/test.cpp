#include <memory>
#include <vector>
#include <cstring>
#include <algorithm>
#include <map>
#include <iostream>
#include "EasyH5File.hpp"

int main(int argc, char* argv[]) {
    EasyH5File f("test_out");
    f.addGroup("/grp");
    std::vector<double> v({1.0, 2.0, 3.0, 4.0});
    f.writeVectorToGroup(v, "/grp", "vals");
    std::vector<std::string> s({"hi", "hello", "hola"});
    f.writeVectorToGroup(s, "/grp", "strs");
}
