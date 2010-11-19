#ifndef OPENCL_CXX_KERNEL_HPP
#define OPENCL_CXX_KERNEL_HPP 

// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

namespace OpenCL {
    class Kernel {
        public:
            Kernel(Program program, const char * name);
            Kernel(const Kernel& other);
            Kernel& operator=(const Kernel& other);
            ~Kernel();

            template <typename T>
            SetArg(T arg, unsigned int index);

            // This is using C++0x variadic templates
            template <typename... Args>
                Kernel& operator()(Args&... args){
                    return RecursiveSetArg(0,args...);
                }
        private:
            Kernel(); // Not implemented
            template <typename T, typename... Args>
                Kernel& RecursiveSetArg(unsigned int index,
                        T arg1, Arg... rest);

            cl_kernel cl_impl;
    }
}

#endif 
