CC=gcc
CFLAGS=-Wall -Werror=vla -std=c11
LDLIBS=-lm

test: my_dgemv_v2.o

clean:
	-$(RM) -rf test *.o

.PHONY: clean