#ifndef OPENCL_CXX_CONTEXT_HPP
#define OPENCL_CXX_CONTEXT_HPP 

// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/opencl.hpp>
#include <opencl-cxx/devicetype.hpp>
#include <vector>

namespace OpenCL {
    class Platform;
    class Device;

    class Context {
        public:
            Context(enum DeviceType::type type = 
                    DeviceType::Default);
            Context(std::vector<Device> devices);

            Context(const Context& other);
            Context& operator=(const Context& other);
            ~Context();

            std::vector<Device> getAllDevices();
            Device getDefaultDevice();

        private:
            friend class Program;
            Context(cl_context impl):cl_impl(impl){}
            cl_context cl_impl;
            unsigned int ReferenceCount() const;
            Context& Retain();
    };
}

#endif 
