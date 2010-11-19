// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/platform.hpp>
#include <opencl-cxx/device.hpp>

using namespace OpenCL;

std::vector<Platform> Platform::All(){
    cl_uint num_platforms;

    clGetPlatformIDs(0,NULL,&num_platforms);
    cl_platform_id * platform_ids = new cl_platform_id[num_platforms];
    clGetPlatformIDs(num_platforms,platform_ids,NULL);

    std::vector<Platform> platforms;
    for (size_t i=0;i<num_platforms;++i){
        platforms.push_back(Platform(platform_ids[i]));
    }

    delete[] platform_ids;
    return platforms;
}

Platform Platform::Default(){
    return All()[0];
}

std::vector<Device> Platform::getAllDevices(enum DeviceType::type type){
    cl_uint num_devices;

    clGetDeviceIDs(cl_impl,type,0,NULL,&num_devices);
    cl_device_id * device_ids = new cl_device_id[num_devices];
    clGetDeviceIDs(cl_impl,type,num_devices,device_ids,NULL);

    std::vector<Device> devices;
    for (size_t i=0;i<num_devices;++i){
        devices.push_back(Device(device_ids[i]));
    }

    delete[] device_ids;
    return devices;
}

Device Platform::getDefaultDevice(enum DeviceType::type type){
    return getAllDevices(type)[0];
}
