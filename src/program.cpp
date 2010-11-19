// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/program.hpp>

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
}

Program::Program(const Program& other){
    clRetainProgram(other.cl_impl);
    cl_impl = other.cl_impl;
}
Program& Program::operator=(const Program& other){
    clRetainProgram(other.cl_impl);
    cl_context copy = other.cl_impl;
    cl_impl = other.cl_impl;
    clReleaseProgram(copy);
    return *this;
}
Program::~Program(){
    clReleaseProgram(cl_impl);
}

void Program::Build() {
    Build(getContext().getAllDevices());
}
void Program::Build(std::vector<Device> devices){
    cl_device_id * device_ids = new cl_device_id[devices.size()];
    for (size_t i=0;i<devices.size();++i){
        device_ids[i] = devices[i].cl_impl;
    }
    clBuildProgram(cl_impl,
            devices.size(),
            device_ids,
            NULL,NULL,NULL);
}

Context Program::getContext();
std::vector<Device> Program::getDevices();

std::vector<std::string> Program::Source();
std::vector<std::vector<unsigned char> > Program::Binaries();

std::string Program::BuildLog();
std::string Program::BuildOptions();
cl_build_status Program::BuildStatus();
