#ifndef OPENCL_CXX_DEVICE_HPP
#define OPENCL_CXX_DEVICE_HPP 

// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/opencl.hpp>
#include <opencl-cxx/devicetype.hpp>
#include <vector>
#include <string>

namespace OpenCL {
    class Platform;
    /// An OpenCL device
    class Device {
        public:
            /// All available devices on the default platform
            static std::vector<Device> All(enum DeviceType::type type 
                    = DeviceType::Default);
            /// Default device on the default platform
            static Device Default(enum DeviceType::type type
                    = DeviceType::Default);

            DeviceType Type();
            cl_uint VendorId();
            cl_uint MaxComputeUnits();
            cl_uint MaxWorkItemDimensions();
            std::vector<cl_uint> MaxWorkGroupSize();
            std::vector<cl_uint> MaxWorkItemSizes();
            cl_uint PreferredVectorWidthChar();
            cl_uint PreferredVectorWidthShort();
            cl_uint PreferredVectorWidthInt();
            cl_uint PreferredVectorWidthLong();
            cl_uint PreferredVectorWidthFloat();
            cl_uint PreferredVectorWidthDouble();
            cl_uint MaxClockFrequency();
            cl_uint AddressBits();
            cl_uint MaxReadImageArgs();
            cl_uint MaxWriteImageArgs();
            cl_ulong MaxMemAllocSize();
            size_t Image2dMaxWidth();
            size_t Image2dMaxHeight();
            size_t Image3dMaxWidth();
            size_t Image3dMaxHeight();
            size_t Image3dMaxDepth();
            cl_bool ImageSupport();
            size_t MaxParameterSize();
            cl_uint MaxSamplers();
            cl_uint MemBaseAddrAlign();
            cl_uint MinDataTypeAlignSize();
            cl_device_fp_config SingleFpConfig();
            cl_device_mem_cache_type GlobalMemCacheType();
            cl_uint GlobalMemCachelineSize();
            cl_ulong GlobalMemCacheSize();
            cl_ulong GlobalMemSize();
            cl_ulong MaxConstantBufferSize();
            cl_uint MaxConstantArgs();
            cl_device_local_mem_type LocalMemType();
            cl_ulong LocalMemSize();
            cl_bool ErrorCorrectionSupport();
            size_t ProfilingTimerResolution();
            cl_bool EndianLittle();
            cl_bool Available();
            cl_bool CompilerAvailable();
            cl_device_exec_capabilities ExecutionCapabilities();
            cl_command_queue_properties QueueProperties();
            std::string Name();
            std::string Vendor();
            std::string DriverVersion();
            std::string Profile();
            std::string Version();
            std::vector<std::string> Extensions();
            Platform getPlatform();

        private:
            friend class Platform;
            friend class Context;
            friend class Program;
            Device(cl_device_id cl_impl):cl_impl(cl_impl){}
            Device(); // Not implemented

            cl_device_id cl_impl;
    };
}

#endif 
