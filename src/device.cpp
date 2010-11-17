// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/device.hpp>
#include <opencl-cxx/platform.hpp>

using namespace OpenCL;

std::vector<Device> Device::All(enum DeviceType::type type){
    return Platform::Default().getAllDevices(type);
}

Device Device::Default(enum DeviceType::type type){
    return Platform::Default().getDefaultDevice(type);
}
