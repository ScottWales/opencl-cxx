// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/device.hpp>
#include <iostream>

int main(){
    // Construction
    OpenCL::Device device1 = OpenCL::Device::Default(OpenCL::DeviceType::CPU);
    OpenCL::Device device2(device1);
    OpenCL::Device device3 = OpenCL::Device::Default(OpenCL::DeviceType::GPU);
    device2 = device3;

    std::vector<OpenCL::Device> devices = 
        OpenCL::Device::All(OpenCL::DeviceType::All);
    for (size_t i=0;i<devices.size();++i){
        std::cout<<devices[i].Name()<<"  |  "
           <<devices[i].Vendor()<<"  |  "
           <<devices[i].Version()<<"  |  "
           <<devices[i].DriverVersion()<<"  |  "
           <<devices[i].Profile()<<"\n";
        std::vector<std::string> extensions = devices[i].Extensions();
        for (size_t j=0;j<extensions.size();++j){
            std::cout<<"\t"<<extensions[j]<<"\n";
        }
    }

    return 0;
}
