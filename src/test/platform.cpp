// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/platform.hpp>

int main(){
    // Construction
    OpenCL::Platform platform1 = OpenCL::Platform::Default();
    OpenCL::Platform platform2(platform1);
    OpenCL::Platform platform3 = OpenCL::Platform::Default();
    platform2 = platform3;

    return 0;
}
