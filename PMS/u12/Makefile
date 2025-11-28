CXX=g++
CPPFLAGS=
CXXFLAGS=-Wall -std=c++11
LDFLAGS=
LDLIBS=
LINK.o=$(CXX) $(LDFLAGS)

all: hello integer

hello: hello.cpp
integer: integer.cpp
### Insert targets and prerequisites below
# target: integer.cpp hello.cpp

.PHONY: clean
clean:
	-$(RM) *.o hello integer