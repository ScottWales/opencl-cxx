# Copyright Scott Wales 2010
# Distributed under the Boost Software Licence, Version 1.0.
# (See accompanying file LICENCE_1_0.txt or copy at
# http://www.boost.org/LICENCE_1_0.txt)

BOOST=/usr/local/boost
BOOST_INCDIR=$(BOOST)/include

OPENCL=/usr/local
OPENCL_INCDIR=$(OPENCL)/include
OPENCL_LIBDIR=$(OPENCL)/lib
OPENCL_LIB=-framework OpenCL

CPPFLAGS+=-MMD -MP -MF build/$*.dep
CPPFLAGS+=-I./include
CPPFLAGS+=-I$(BOOST_INCDIR) -I$(OPENCL_INCDIR)
CPPFLAGS+=-Wall -Werror -Wextra

CXXFLAGS+=-O2 -g

LDFLAGS+=-L$(OPENCL_LIBDIR)
LDLIBS+=$(OPENCL_LIB)

all:check
check:test/platform test/device test/context test/program
clean:

.PHONY:all check clean

test/platform:build/platform.o
test/device:build/device.o build/platform.o
test/context:build/context.o build/device.o build/platform.o
test/program:build/program.o build/context.o build/device.o build/platform.o

build/%.o:src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
test/%:build/test/%.o
	mkdir -p $(dir $@)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	./$@
