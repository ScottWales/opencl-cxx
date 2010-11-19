// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/context.hpp>
#include <opencl-cxx/device.hpp>

int main(){
    // Construction
    OpenCL::Context context1 = OpenCL::Context(OpenCL::DeviceType::CPU);
    OpenCL::Context context2(context1);
    OpenCL::Context context3 = OpenCL::Context();
    context2 = context3;

    std::vector<OpenCL::Device> devices = context1.getAllDevices();
    OpenCL::Device device = context3.getDefaultDevice();

    return 0;
}
