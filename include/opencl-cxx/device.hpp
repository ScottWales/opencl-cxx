#ifndef OPENCL_CXX_DEVICE_HPP
#define OPENCL_CXX_DEVICE_HPP 

// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/opencl.hpp>
#include <opencl-cxx/devicetype.hpp>
#include <vector>

namespace OpenCL {
    /// An OpenCL device
    class Device {
        public:
            /// All available devices on the default platform
            static std::vector<Device> All(enum DeviceType::type type 
                    = DeviceType::Default);
            /// Default device on the default platform
            static Device Default(enum DeviceType::type type
                    = DeviceType::Default);
        private:
            Device(cl_device_id cl_impl):cl_impl(cl_impl){}
            Device(); // Not implemented

            cl_device_id cl_impl;
    };
}

#endif 
