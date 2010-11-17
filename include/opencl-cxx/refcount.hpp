#ifndef OPENCL_CXX_REFCOUNT_HPP
#define OPENCL_CXX_REFCOUNT_HPP 

// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

namespace OpenCL {

    /// Wrapper handling OpenCL reference counting
    template <typename ImplT>
        class RefCounted {
            public:
                RefCounted(ImplT cl_impl):cl_impl(cl_impl){};
                RefCounted(const RefCounted& other){
                    other.Retain(other.cl_impl);
                    cl_impl = other.cl_impl;
                }
                RefCounted& operator=(const RefCounted& other){
                    other.Retain(other.cl_impl);
                    ImplT copy = cl_impl;
                    cl_impl = other.cl_impl;
                    Release(copy);
                }
                ~RefCounted(){
                    Release(cl_impl);
                }

            protected:
                /// Retains the provided implementation
                virtual void Retain(ImplT impl) = 0;
                /// Releases the provided implementation
                virtual void Release(ImplT impl) = 0;
                ImplT cl_impl;
        }
}

#endif 
