// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/kernel.hpp>
#include <opencl-cxx/program.hpp>
#include <opencl-cxx/context.hpp>
#include <opencl-cxx/device.hpp>
#include <sstream>
#include <iostream>
#include <boost/exception.hpp>

using namespace OpenCL;

int main(){
    try {
        Context context;
        std::vector<Device> devices = context.getAllDevices();
        for (size_t i=0;i<devices.size();++i){
            std::cout<<devices[i].Name()<<"\n";
        }

        std::string source = "__kernel void test(int a, float b){a*=2;b+=a;}";
        std::stringstream stream(source);

        Program program(context,stream);
        std::cout<<program.Source()<<"\n";
        program.Build();
        for (size_t i=0;i<devices.size();++i){
            std::cout<<program.BuildLog(devices[i])<<"\n";
        }

        Kernel kernel = Kernel(program,"test");
        cl_int a = 2;
        cl_float b = 3.14;
        kernel(a,b);

    } catch (boost::exception& e) {
        std::cerr<<diagnostic_information(e);
        throw;
    }
    return 0;
}

