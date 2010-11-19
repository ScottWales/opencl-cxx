// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/context.hpp>
#include <opencl-cxx/platform.hpp>
#include <opencl-cxx/device.hpp>

using namespace OpenCL;

std::vector<Device> Context::getAllDevices(enum DeviceType::type type){
    (void)type;
    std::vector<Device> devices;
    return devices;
}

Device Context::getDefaultDevice(enum DeviceType::type type){
    return getAllDevices(type)[0];
}
