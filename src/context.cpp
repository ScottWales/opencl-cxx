// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/context.hpp>
#include <opencl-cxx/platform.hpp>
#include <opencl-cxx/device.hpp>
#include <opencl-cxx/error.hpp>

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
    CLCheck(errcode);
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
    CLCheck(errcode);
}

Context::Context(const Context& other){
    CLCheck(clRetainContext(other.cl_impl));
    cl_impl = other.cl_impl;
}
Context& Context::operator=(const Context& other){
    CLCheck(clRetainContext(other.cl_impl));
    cl_context copy = other.cl_impl;
    cl_impl = other.cl_impl;
    CLCheck(clReleaseContext(copy));
    return *this;
}
Context::~Context(){
    CLCheck(clReleaseContext(cl_impl));
}

namespace {
    template <typename T>
        struct Info {
            static T get(cl_context cl_impl, cl_context_info param){
                T result;
                CLCheck(clGetContextInfo(cl_impl, param, sizeof(T),&result,NULL));
                return result;
            }
        };
    template <typename T>
        struct Info<std::vector<T> > {
            static std::vector<T> get(cl_context cl_impl, cl_context_info param){
                size_t size;
                CLCheck(clGetContextInfo(cl_impl, param, 0,NULL,&size));
                size_t length = size/sizeof(T);
                T * result = new T[length];
                CLCheck(clGetContextInfo(cl_impl, param, size,result,NULL));
                std::vector<T> resultvector(result,result+length);
                delete[] result;
                return resultvector;
            }
        };
    template <>
        struct Info<std::string> {
            static std::string get(cl_context cl_impl, cl_context_info param){
                size_t size;
                CLCheck(clGetContextInfo(cl_impl, param, 0,NULL,&size));
                char * result = new char[size];
                CLCheck(clGetContextInfo(cl_impl, param, size,result,NULL));
                std::string resultstring(result);
                delete[] result;
                return resultstring;
            }
        };
}

std::vector<Device> Context::getAllDevices(){
    std::vector<cl_device_id> device_ids = 
        Info<std::vector<cl_device_id> >::get(cl_impl,CL_CONTEXT_DEVICES);
    std::vector<Device> devices;
    for (size_t i=0;i<device_ids.size();++i){
        devices.push_back(Device(device_ids[i]));
    }
    return devices;
}

Device Context::getDefaultDevice(){
    return getAllDevices().at(0);
}
