// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/opencl.hpp>
#include <opencl-cxx/error.hpp>
#include <opencl-cxx/context.hpp>
#include <opencl-cxx/device.hpp>

using namespace OpenCL;

CommandQueue::CommandQueue(Context context){
    Device device = context.getDefaultDevice();
    cl_int errcode;
    cl_impl = clCreateCommandQueue(context.cl_impl,
            device.cl_impl,
            0,
            &errcode);
    CLCheck(errcode);
}
CommandQueue::CommandQueue(Context context, Device device){
    cl_int errcode;
    cl_impl = clCreateCommandQueue(context.cl_impl,
            device.cl_impl,
            0,
            &errcode);
    CLCheck(errcode);
}

CommandQueue::CommandQueue(const CommandQueue& other){
    CLCheck(clRetainCommandQueue(other.cl_impl));
    cl_impl = other.cl_impl;
}
CommandQueue& CommandQueue::operator=(const CommandQueue& other){
    CLCheck(clRetainCommandQueue(other.cl_impl));
    cl_command_queue copy = cl_impl;
    cl_impl = other.cl_impl;
    CLCheck(clReleaseCommandQueue(copy));
    return *this;
}
CommandQueue::~CommandQueue(){
    CLCheck(clReleaseCommandQueue(cl_impl));
}
