all: include/EasyH5File.hpp include/EasyH5Utils.hpp src/EasyH5Utils.cpp
	mkdir -p bin
	c++ -std=c++11 -I include -o bin/test src/test.cpp src/EasyH5Utils.cpp -lhdf5
clean:
	bin/test
