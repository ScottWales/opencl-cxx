// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/platform.hpp>
#include <opencl-cxx/device.hpp>

int main(){
    // Construction
    OpenCL::Platform platform1 = OpenCL::Platform::Default();
    OpenCL::Platform platform2(platform1);
    OpenCL::Platform platform3 = OpenCL::Platform::Default();
    platform2 = platform3;

    std::vector<OpenCL::Platform> platforms = OpenCL::Platform::All();

    // Device access
    for (size_t i=0;i<platforms.size();++i){
        std::vector<OpenCL::Device> devices = platforms[i].getAllDevices();
    }

    return 0;
}
