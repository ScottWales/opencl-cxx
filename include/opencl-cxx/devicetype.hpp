#ifndef OPENCL_CXX_DEVICETYPE_HPP
#define OPENCL_CXX_DEVICETYPE_HPP 

// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/opencl.hpp>

namespace OpenCL {
    /// Enumeration of the types of devices
    struct DeviceType {
        enum type {
            All = OPENCL_DEVICE_TYPE_ALL,
            Default = OPENCL_DEVICE_TYPE_DEFAULT,
            CPU = OPENCL_DEVICE_TYPE_CPU,
            GPU = OPENCL_DEVICE_TYPE_GPU,
            Accelerator = OPENCL_DEVICE_TYPE_ACCELERATOR,
        }
    }
}


#endif 
