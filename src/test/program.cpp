// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/program.hpp>
#include <opencl-cxx/context.hpp>
#include <sstream>
#include <iostream>

using namespace OpenCL;

int main(){
    Context context;

    std::string source = "__kernel void test(int a){a*=2;}";
    std::stringstream stream(source);

    Program program(context,stream);
    std::cout<<program.Source()<<"\n";
    program.Build();

    return 0;
}

