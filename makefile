BOOST=/usr/local/boost
BOOST_INCDIR=$(BOOST)/include

OPENCL=/usr/local
OPENCL_INCDIR=$(OPENCL)/include
OPENCL_LIBDIR=$(OPENCL)/lib
OPENCL_LIB=-framework OpenCL

CPPFLAGS+=-MMD -MP -MF $@.dep
CPPFLAGS+=-I./include
CPPFLAGS+=-I$(BOOST_INCDIR) -I$(OPENCL_INCDIR)

CXXFLAGS+=-O2 -g

LDFLAGS+=-L$(OPENCL_LIBDIR)
LDLIBS+=$(OPENCL_LIB)

all:
check:
clean:

.PHONY:all check clean
