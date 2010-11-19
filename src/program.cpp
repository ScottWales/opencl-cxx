// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/program.hpp>
#include <opencl-cxx/context.hpp>
#include <opencl-cxx/device.hpp>
#include <opencl-cxx/error.hpp>

using namespace OpenCL;

namespace {
    std::vector<char> ReadSource(std::istream& stream){
        std::vector<char> buffer(1024);
        std::vector<char> output;
        while (!stream.eof()){
            stream.read(&buffer[0],buffer.size());
            output.insert(output.end(),buffer.begin(),buffer.end());
        }
        return output;
    }
}

Program::Program(Context context, std::istream& stream){
    cl_int errcode;
    std::vector<char> source = ReadSource(stream);
    const char * source_ptr = &source[0];
    cl_impl = clCreateProgramWithSource(context.cl_impl,
            1,
            &source_ptr,
            NULL,
            &errcode);
    CLCheck(errcode);
}

Program::Program(const Program& other){
    CLCheck(clRetainProgram(other.cl_impl));
    cl_impl = other.cl_impl;
}
Program& Program::operator=(const Program& other){
    CLCheck(clRetainProgram(other.cl_impl));
    cl_program copy = cl_impl;
    cl_impl = other.cl_impl;
    CLCheck(clReleaseProgram(copy));
    return *this;
}
Program::~Program(){
    CLCheck(clReleaseProgram(cl_impl));
}

void Program::Build() {
    Build(getContext().getAllDevices());
}
void Program::Build(std::vector<Device> devices){
    std::vector<cl_device_id> device_ids;
    for (size_t i=0;i<devices.size();++i){
        device_ids.push_back(devices[i].cl_impl);
    }
    CLCheck(clBuildProgram(cl_impl, devices.size(), &device_ids[0], "",NULL,NULL));
}

namespace {
    template <typename T>
        struct Info {
            static T get(cl_program cl_impl, cl_program_info param){
                T result;
                CLCheck(clGetProgramInfo(cl_impl, param, sizeof(T),&result,NULL));
                return result;
            }
        };
    template <typename T>
        struct Info<std::vector<T> > {
            static std::vector<T> get(cl_program cl_impl, cl_program_info param){
                size_t size;
                CLCheck(clGetProgramInfo(cl_impl, param, 0,NULL,&size));
                size_t length = size/sizeof(T);
                T * result = new T[length];
                CLCheck(clGetProgramInfo(cl_impl, param, size,result,NULL));
                std::vector<T> resultvector(result,result+length);
                delete[] result;
                return resultvector;
            }
        };
    template <>
        struct Info<std::string> {
            static std::string get(cl_program cl_impl, cl_program_info param){
                size_t size;
                CLCheck(clGetProgramInfo(cl_impl, param, 0,NULL,&size));
                char * result = new char[size];
                CLCheck(clGetProgramInfo(cl_impl, param, size,result,NULL));
                std::string resultstring(result);
                delete[] result;
                return resultstring;
            }
        };
}

Context Program::getContext(){
    return Context(Info<cl_context>::get(cl_impl,CL_PROGRAM_CONTEXT)).Retain();
}

std::vector<Device> Program::getDevices(){
    std::vector<cl_device_id> device_ids = 
        Info<std::vector<cl_device_id> >::get(cl_impl,CL_PROGRAM_DEVICES);
    std::vector<Device> devices;
    for (size_t i=0;i<device_ids.size();++i){
        devices.push_back(device_ids[i]);
    }
    return devices;
}

std::string Program::Source(){
    return Info<std::string>::get(cl_impl,CL_PROGRAM_SOURCE);
}
/*
   std::vector<std::vector<unsigned char> > Program::Binaries();

   std::string Program::BuildLog();
   std::string Program::BuildOptions();
   cl_build_status Program::BuildStatus();
   */
