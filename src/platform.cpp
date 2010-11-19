// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/platform.hpp>
#include <opencl-cxx/device.hpp>
#include <string>
#include <sstream>

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
    return All().at(0);
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
    return getAllDevices(type).at(0);
}

namespace {
    template <typename T>
        struct Info {
            static T get(cl_platform_id impl, cl_platform_info param){
                T result;
                clGetPlatformInfo(impl, param,
                        sizeof(T),&result,NULL);
                return result;
            }
        };
    template <typename T>
        struct Info<std::vector<T> > {
            static std::string get(cl_platform_id impl, cl_platform_info param){
                size_t size;
                clGetPlatformInfo(impl, param,
                        0,NULL,&size);
                size_t length = size/sizeof(T);
                T * result = new T[length];
                clGetPlatformInfo(impl, param,
                        size,result,NULL);
                std::vector<T> resultvector(result,result+length);
                delete[] result;
                return resultvector;
            }
        };
    template <>
        struct Info<std::string> {
            static std::string get(cl_platform_id impl, cl_platform_info param){
                size_t size;
                clGetPlatformInfo(impl, param,
                        0,NULL,&size);
                char * result = new char[size];
                clGetPlatformInfo(impl, param,
                        size,result,NULL);
                std::string resultstring(result);
                delete[] result;
                return resultstring;
            }
        };
}


std::string Platform::Profile() {
    return Info<std::string>::get(cl_impl,CL_PLATFORM_PROFILE);
}
std::string Platform::Version() {
    return Info<std::string>::get(cl_impl,CL_PLATFORM_VERSION);
}
std::string Platform::Name() {
    return Info<std::string>::get(cl_impl,CL_PLATFORM_NAME);
}
std::string Platform::Vendor() {
    return Info<std::string>::get(cl_impl,CL_PLATFORM_VENDOR);
}
std::vector<std::string> Platform::Extensions() {
    std::string input = Info<std::string>::get(cl_impl,CL_PLATFORM_EXTENSIONS);
    std::string buffer;
    std::stringstream stream(input);
    std::vector<std::string> tokens;
    while (stream >> buffer){
        tokens.push_back(buffer);
    }
    return tokens;
}

