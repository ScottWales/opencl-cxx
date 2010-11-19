#ifndef OPENCL_CXX_PLATFORM_HPP
#define OPENCL_CXX_PLATFORM_HPP 

// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/opencl.hpp>
#include <opencl-cxx/devicetype.hpp>
#include <vector>

namespace OpenCL {
    class Device;
    /// An OpenCL platform
    class Platform {
        public:
            /// All available platforms
            static std::vector<Platform> All();
            /// Default platform
            static Platform Default();
            
            /// Get all devices on the platform
            std::vector<Device> getAllDevices(enum DeviceType::type type
                    = DeviceType::Default);
            /// Get the default device on the platform
            Device getDefaultDevice(enum DeviceType::type type
                    = DeviceType::Default);

            std::string Profile();
            std::string Version();
            std::string Name();
            std::string Vendor();
            std::vector<std::string> Extensions();

        private:
            friend class Context;
            friend class Device;
            Platform(cl_platform_id cl_impl):cl_impl(cl_impl){}
            Platform(); // Not implemented

            cl_platform_id cl_impl;
    };
}


#endif 
