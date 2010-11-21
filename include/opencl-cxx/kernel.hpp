#ifndef OPENCL_CXX_KERNEL_HPP
#define OPENCL_CXX_KERNEL_HPP 

// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/opencl.hpp>
#include <opencl-cxx/error.hpp>
//#if ( __cplusplus <= 199711L )
//#warning <openncl-cxx/kernel.hpp> uses C++0x variadic templates for full functionality
//#endif

namespace OpenCL {
    class Program;
    class Kernel {
        public:
            Kernel(Program program, const char * name);
            Kernel(const Kernel& other);
            Kernel& operator=(const Kernel& other);
            ~Kernel();

            template <typename T>
                Kernel& SetArg(unsigned int index, T arg);

//#if ( __cplusplus > 199711L )
            // This is using C++0x variadic templates
            template <typename T, typename... Args>
                Kernel& SetArg(unsigned int index,
                        T arg1, Args... rest);

            template <typename... Args>
                Kernel& operator()(Args&... args){
                    return SetArg(0,args...);
                }
//#endif

        private:
            Kernel(); // Not implemented
            Kernel(cl_kernel impl):cl_impl(impl){}

            cl_kernel cl_impl;
    };

//#if ( __cplusplus > 199711L )
    template <typename T, typename... Args>
        inline Kernel& Kernel::SetArg(unsigned int index,
                T arg1, Args... rest){
            SetArg(index,arg1);
            return SetArg(index+1,rest...);
        }
//#endif
    template <typename T>
        inline Kernel& Kernel::SetArg(unsigned int index,
                T arg){
            CLCheck(clSetKernelArg(cl_impl,
                        index,
                        sizeof(arg),
                        &arg));
            return *this;
        }
}

#endif 
