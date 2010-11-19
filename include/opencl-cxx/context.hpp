#ifndef OPENCL_CXX_CONTEXT_HPP
#define OPENCL_CXX_CONTEXT_HPP 

// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/opencl.hpp>
#include <opencl-cxx/refcounted.hpp>
#include <opencl-cxx/devicetype.hpp>

namespace OpenCL {
    class Platform;
    class Device;

    class Context: public RefCounted<cl_context> {
        public:
            Context();
            Context(Platform platform);
            Context(std::vector<Device> devices);
            Context(std::vector<Device> devices,
                    Platform platform);

            std::vector<Device> getAllDevices(enum DeviceType::type type
                    = DeviceType::All);
            Device getDefaultDevice(enum DeviceType::type type
                    = DeviceType::All);


        protected:
            virtual void Retain(cl_context impl);
            virtual void Release(cl_context impl);
    }
}

#endif 
