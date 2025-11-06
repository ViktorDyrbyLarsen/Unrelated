OPT = -O3
OPENMP = 
MSPTDIR = msptools

CC = gcc
CPPFLAGS = -I$(MSPTDIR)/include/
CFLAGS = -Wall -std=c99 $(OPT) $(OPENMP)
LDFLAGS = -L$(MSPTDIR)/lib -L.
LDLIBS = -lmsptools -lm
OBJS = my_dgemv.o my_dgemv_v1.o my_dgemv_v2.o datatools.o

.PHONY: all msptools clean distclean

all: msptools main

main: $(OBJS)

msptools:
	make --directory=msptools

clean:
	-$(RM) *.o main

distclean: clean
	make --no-print-directory --directory=msptools clean
