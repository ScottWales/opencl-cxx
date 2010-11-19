#ifndef OPENCL_CXX_ERROR_HPP
#define OPENCL_CXX_ERROR_HPP 

// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <exception>
#include <boost/exception.hpp>

namespace OpenCL {

#define CLCheck(x) CLCheckImpl(x,__FILE__,__LINE__,__func__)

    class RuntimeError : 
        public virtual boost::exception,
        public virtual std::exception 
    {
        public:
            RuntimeError(int errcode):errcode(errcode){}
            int errcode;
    };

    inline void CLCheckImpl(int errcode, 
            const char * file,
            long long line,
            const char * function){
        if (errcode != 0){
            ::boost::throw_exception( 
                    ::boost::enable_error_info(RuntimeError(errcode)) <<
                    ::boost::throw_function(function) <<
                    ::boost::throw_file(file) <<
                    ::boost::throw_line(line) );
        }
    }

}

#endif 
