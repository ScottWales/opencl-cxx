// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/kernel.hpp>
#include <opencl-cxx/program.hpp>
#include <opencl-cxx/error.hpp>

using namespace OpenCL;

Kernel::Kernel(Program program,
        const char * name){
    cl_int errcode;
    cl_impl = clCreateKernel(program.cl_impl,
            name,
            &errcode);
    CLCheck(errcode);
}

Kernel::Kernel(const Kernel& other){
    CLCheck(clRetainKernel(other.cl_impl));
    cl_impl = other.cl_impl;
}
Kernel& Kernel::operator=(const Kernel& other){
    CLCheck(clRetainKernel(other.cl_impl));
    cl_kernel copy = cl_impl;
    cl_impl = other.cl_impl;
    CLCheck(clReleaseKernel(copy));
    return *this;
}
Kernel::~Kernel(){
    CLCheck(clReleaseKernel(cl_impl));
}
