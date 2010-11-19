// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/context.hpp>
#include <opencl-cxx/platform.hpp>
#include <opencl-cxx/device.hpp>

using namespace OpenCL;

Context::Context(enum DeviceType::type type){
    cl_int errcode;
    cl_context_properties properties[] = {
        CL_CONTEXT_PLATFORM,
        (cl_context_properties)Platform::Default().cl_impl,
        0};
    cl_impl = clCreateContextFromType(properties,
            type,
            clLogMessagesToStderrAPPLE,
            NULL,
            &errcode);
}

Context::Context(std::vector<Device> devices){
    cl_int errcode;
    cl_context_properties properties[] = {
        CL_CONTEXT_PLATFORM,
        (cl_context_properties)Platform::Default().cl_impl,
        0};
    cl_device_id * device_ids = new cl_device_id[devices.size()];
    for (size_t i=0;i<devices.size();++i){
        device_ids[i] = devices[i].cl_impl;
    }
    cl_impl = clCreateContext(properties,
            devices.size(),
            device_ids,
            clLogMessagesToStderrAPPLE,
            NULL,
            &errcode);
    delete[] device_ids;
}

Context::Context(const Context& other){
    clRetainContext(other.cl_impl);
    cl_impl = other.cl_impl;
}
Context& Context::operator=(const Context& other){
    clRetainContext(other.cl_impl);
    cl_context copy = other.cl_impl;
    cl_impl = other.cl_impl;
    clReleaseContext(copy);
    return *this;
}
Context::~Context(){
    clReleaseContext(cl_impl);
}

std::vector<Device> Context::getAllDevices(enum DeviceType::type type){
    (void)type;
    std::vector<Device> devices;
    return devices;
}

Device Context::getDefaultDevice(enum DeviceType::type type){
    return getAllDevices(type).at(0);
}
