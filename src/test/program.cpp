// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

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

        std::string source = "__kernel void test(int a){a*=2;}";
        std::stringstream stream(source);

        Program program(context,stream);
        std::cout<<program.Source()<<"\n";
        program.Build();
        for (size_t i=0;i<devices.size();++i){
            std::cout<<program.BuildLog(devices[i])<<"\n";
        }

    } catch (boost::exception& e) {
        std::cerr<<diagnostic_information(e);
        throw;
    }
    return 0;
}

