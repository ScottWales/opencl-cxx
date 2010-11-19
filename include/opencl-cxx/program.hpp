#ifndef OPENCL_CXX_PROGRAM_HPP
#define OPENCL_CXX_PROGRAM_HPP 

// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/opencl.hpp>
#include <istream>

namespace OpenCL {
    class Context;
    class Device;

    class Program {
        public:
            Program(Context context, std::istream& stream);

            Program(const Program& other);
            Program& operator=(const Program& other);
            ~Program();

            Build();
            Build(std::vector<Device> devices);

            Context getContext();
            std::vector<Device> getDevices();

            std::vector<std::string> Source();
            std::vector<std::vector<unsigned char> > Binaries();

            std::string BuildLog();
            std::string BuildOptions();
            cl_build_status BuildStatus();

        private:
            Program(); // Not implemented
            Program(cl_program impl):cl_impl(impl){}

            cl_program cl_impl;
    };
}

#endif 
