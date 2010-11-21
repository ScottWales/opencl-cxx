#ifndef OPENCL_CXX_COMMANDQUEUE_HPP
#define OPENCL_CXX_COMMANDQUEUE_HPP 

// Copyright Scott Wales 2010
// Distributed under the Boost Software Licence, Version 1.0.
// (See accompanying file LICENCE_1_0.txt or copy at
// http://www.boost.org/LICENCE_1_0.txt)

#include <opencl-cxx/opencl.hpp>
#include <vector>

namespace OpenCL {
    class Event;
    class Context;
    class Device;

    class CommandQueue {
        public:
            CommandQueue(Context context);
            CommandQueue(Context context, Device device);

            CommandQueue(const CommandQueue& other);
            CommandQueue& operator=(const CommandQueue& other);
            ~CommandQueue();

            /// Add a single action
            template <typename T>
                std::vector<Event> Add(T action);

            /// Add a list of actions to be evaluated in sequence
            template <typename T, typename Args...>
                std::vector<Event> Add(T action1, Args... rest);

            /// Add a list of actions to be evaluated in sequence
            template <typename Args...>
                std::vector<Event> operator()(Args... args){
                    return Add(args...);
                }
        private:
            CommandQueue(); // Not implemented
            CommandQueue(cl_commandqueue impl):cl_impl(impl){};

            cl_command_queue cl_impl;
    };
}

#endif 
