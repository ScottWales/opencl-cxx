// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/device.hpp>
#include <opencl-cxx/platform.hpp>
#include <string>
#include <sstream>

using namespace OpenCL;

std::vector<Device> Device::All(enum DeviceType::type type){
    return Platform::Default().getAllDevices(type);
}

Device Device::Default(enum DeviceType::type type){
    return Platform::Default().getDefaultDevice(type);
}

namespace {
    template <typename T>
        struct Info {
            static T get(cl_device_id cl_impl, cl_device_info param){
                T result;
                clGetDeviceInfo(cl_impl, param,
                        sizeof(T),&result,NULL);
                return result;
            }
        };
    template <typename T>
        struct Info<std::vector<T> > {
            static std::vector<T> get(cl_device_id cl_impl, cl_device_info param){
                size_t size;
                clGetDeviceInfo(cl_impl, param,
                        0,NULL,&size);
                size_t length = size/sizeof(T);
                T * result = new T[length];
                clGetDeviceInfo(cl_impl, param,
                        size,result,NULL);
                std::vector<T> resultvector(result,result+length);
                delete[] result;
                return resultvector;
            }
        };
    template <>
        struct Info<std::string> {
            static std::string get(cl_device_id cl_impl, cl_device_info param){
                size_t size;
                clGetDeviceInfo(cl_impl, param,
                        0,NULL,&size);
                char * result = new char[size];
                clGetDeviceInfo(cl_impl, param,
                        size,result,NULL);
                std::string resultstring(result);
                delete[] result;
                return resultstring;
            }
        };
}

DeviceType Device::Type(){
    return DeviceType((enum DeviceType::type)Info<cl_device_type>::get(cl_impl,CL_DEVICE_TYPE));
}
cl_uint Device::VendorId(){
    return Info<cl_uint>::get(cl_impl,CL_DEVICE_VENDOR_ID);
}
cl_uint Device::MaxComputeUnits(){
    return Info<cl_uint>::get(cl_impl,CL_DEVICE_MAX_COMPUTE_UNITS);
}
cl_uint Device::MaxWorkItemDimensions(){
    return Info<cl_uint>::get(cl_impl,CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS);
}
std::vector<cl_uint> Device::MaxWorkGroupSize(){
    return Info<std::vector<cl_uint> >::get(cl_impl,CL_DEVICE_MAX_WORK_GROUP_SIZE);
}
std::vector<cl_uint> Device::MaxWorkItemSizes(){
    return Info<std::vector<cl_uint> >::get(cl_impl,CL_DEVICE_MAX_WORK_ITEM_SIZES);
}
cl_uint Device::PreferredVectorWidthChar(){
    return Info<cl_uint>::get(cl_impl,CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR);
}
cl_uint Device::PreferredVectorWidthShort(){
    return Info<cl_uint>::get(cl_impl,CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT);
}
cl_uint Device::PreferredVectorWidthInt(){
    return Info<cl_uint>::get(cl_impl,CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT);
}
cl_uint Device::PreferredVectorWidthLong(){
    return Info<cl_uint>::get(cl_impl,CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG);
}
cl_uint Device::PreferredVectorWidthFloat(){
    return Info<cl_uint>::get(cl_impl,CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT);
}
cl_uint Device::PreferredVectorWidthDouble(){
    return Info<cl_uint>::get(cl_impl,CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE);
}
cl_uint Device::MaxClockFrequency(){
    return Info<cl_uint>::get(cl_impl,CL_DEVICE_MAX_CLOCK_FREQUENCY);
}
cl_uint Device::AddressBits(){
    return Info<cl_uint>::get(cl_impl,CL_DEVICE_ADDRESS_BITS);
}
cl_uint Device::MaxReadImageArgs(){
    return Info<cl_uint>::get(cl_impl,CL_DEVICE_MAX_READ_IMAGE_ARGS);
}
cl_uint Device::MaxWriteImageArgs(){
    return Info<cl_uint>::get(cl_impl,CL_DEVICE_MAX_WRITE_IMAGE_ARGS);
}
cl_ulong Device::MaxMemAllocSize(){
    return Info<cl_ulong>::get(cl_impl,CL_DEVICE_MAX_MEM_ALLOC_SIZE);
}
size_t Device::Image2dMaxWidth(){
    return Info<size_t>::get(cl_impl,CL_DEVICE_IMAGE2D_MAX_WIDTH);
}
size_t Device::Image2dMaxHeight(){
    return Info<size_t>::get(cl_impl,CL_DEVICE_IMAGE2D_MAX_HEIGHT);
}
size_t Device::Image3dMaxWidth(){
    return Info<size_t>::get(cl_impl,CL_DEVICE_IMAGE3D_MAX_WIDTH);
}
size_t Device::Image3dMaxHeight(){
    return Info<size_t>::get(cl_impl,CL_DEVICE_IMAGE3D_MAX_HEIGHT);
}
size_t Device::Image3dMaxDepth(){
    return Info<size_t>::get(cl_impl,CL_DEVICE_IMAGE3D_MAX_DEPTH);
}
cl_bool Device::ImageSupport(){
    return Info<cl_bool>::get(cl_impl,CL_DEVICE_IMAGE_SUPPORT);
}
size_t Device::MaxParameterSize(){
    return Info<size_t>::get(cl_impl,CL_DEVICE_MAX_PARAMETER_SIZE);
}
cl_uint Device::MaxSamplers(){
    return Info<cl_uint>::get(cl_impl,CL_DEVICE_MAX_SAMPLERS);
}
cl_uint Device::MemBaseAddrAlign(){
    return Info<cl_uint>::get(cl_impl,CL_DEVICE_MEM_BASE_ADDR_ALIGN);
}
cl_uint Device::MinDataTypeAlignSize(){
    return Info<cl_uint>::get(cl_impl,CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE);
}
cl_device_fp_config Device::SingleFpConfig(){
    return Info<cl_device_fp_config>::get(cl_impl,CL_DEVICE_SINGLE_FP_CONFIG);
}
cl_device_mem_cache_type Device::GlobalMemCacheType(){
    return Info<cl_device_mem_cache_type>::get(cl_impl,CL_DEVICE_GLOBAL_MEM_CACHE_TYPE);
}
cl_uint Device::GlobalMemCachelineSize(){
    return Info<cl_uint>::get(cl_impl,CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE);
}
cl_ulong Device::GlobalMemCacheSize(){
    return Info<cl_ulong>::get(cl_impl,CL_DEVICE_GLOBAL_MEM_CACHE_SIZE);
}
cl_ulong Device::GlobalMemSize(){
    return Info<cl_ulong>::get(cl_impl,CL_DEVICE_GLOBAL_MEM_SIZE);
}
cl_ulong Device::MaxConstantBufferSize(){
    return Info<cl_ulong>::get(cl_impl,CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE);
}
cl_uint Device::MaxConstantArgs(){
    return Info<cl_uint>::get(cl_impl,CL_DEVICE_MAX_CONSTANT_ARGS);
}
cl_device_local_mem_type Device::LocalMemType(){
    return Info<cl_device_local_mem_type>::get(cl_impl,CL_DEVICE_LOCAL_MEM_TYPE);
}
cl_ulong Device::LocalMemSize(){
    return Info<cl_ulong>::get(cl_impl,CL_DEVICE_LOCAL_MEM_SIZE);
}
cl_bool Device::ErrorCorrectionSupport(){
    return Info<cl_bool>::get(cl_impl,CL_DEVICE_ERROR_CORRECTION_SUPPORT);
}
size_t Device::ProfilingTimerResolution(){
    return Info<size_t>::get(cl_impl,CL_DEVICE_PROFILING_TIMER_RESOLUTION);
}
cl_bool Device::EndianLittle(){
    return Info<cl_bool>::get(cl_impl,CL_DEVICE_ENDIAN_LITTLE);
}
cl_bool Device::Available(){
    return Info<cl_bool>::get(cl_impl,CL_DEVICE_AVAILABLE);
}
cl_bool Device::CompilerAvailable(){
    return Info<cl_bool>::get(cl_impl,CL_DEVICE_COMPILER_AVAILABLE);
}
cl_device_exec_capabilities Device::ExecutionCapabilities(){
    return Info<cl_device_exec_capabilities>::get(cl_impl,CL_DEVICE_EXECUTION_CAPABILITIES);
}
cl_command_queue_properties Device::QueueProperties(){
    return Info<cl_command_queue_properties>::get(cl_impl,CL_DEVICE_QUEUE_PROPERTIES);
}
std::string Device::Name(){
    return Info<std::string>::get(cl_impl,CL_DEVICE_NAME);
}
std::string Device::Vendor(){
    return Info<std::string>::get(cl_impl,CL_DEVICE_VENDOR);
}
std::string Device::DriverVersion(){
    return Info<std::string>::get(cl_impl,CL_DRIVER_VERSION);
} 
std::string Device::Profile(){
    return Info<std::string>::get(cl_impl,CL_DEVICE_PROFILE);
}
std::string Device::Version(){
    return Info<std::string>::get(cl_impl,CL_DEVICE_VERSION);
}
std::vector<std::string> Device::Extensions(){
    std::string extensions = Info<std::string>::get(cl_impl,CL_DEVICE_EXTENSIONS);
    std::stringstream stream(extensions);

    std::vector<std::string> tokens;
    std::string buffer;
    while (stream >> buffer)
	tokens.push_back(buffer);
    return tokens;
}
Platform Device::getPlatform(){
    return Platform(Info<cl_platform_id>::get(cl_impl,CL_DEVICE_PLATFORM));
}
