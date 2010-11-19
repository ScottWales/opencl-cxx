// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/program.hpp>

using namespace OpenCL;

int main(){
    Context context;

    std::string source = "__kernel void test(int a){a*=2;}";
    std::stringstream stream(source);

    Program program(context,stream);
    program.Build();

    return 0;
}

