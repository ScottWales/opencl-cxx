// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/device.hpp>

int main(){
    // Construction
    OpenCL::Device device1 = OpenCL::Device::Default(OpenCL::DeviceType::CPU);
    OpenCL::Device device2(device1);
    OpenCL::Device device3 = OpenCL::Device::Default(OpenCL::DeviceType::GPU);
    device2 = device3;

    return 0;
}
