CC=gcc
CFLAGS=-Wall -Werror=vla -std=c11

OS_NAME=$(shell uname -s)
ifeq ($(OS_NAME),Linux)
	LDLIBS=-lopenblas -lm
endif
ifeq ($(OS_NAME),Darwin)
	LDLIBS=-lblas -lm
endif

test: dtrsvsolve.o

clean:
	-$(RM) -rf test *.o

.PHONY: clean