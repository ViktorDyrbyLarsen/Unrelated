CC=gcc
CPPFLAGS=-Iinclude
CFLAGS=-Wall -g -std=c99
LDFLAGS=
LDLIBS=-lm
objs=$(patsubst %.c,%.o,$(wildcard src/*.c))

.PHONY: all examples test clean

all: examples 

src/%.o: src/%.c

lib/libmsptools.a: $(objs)
	mkdir -p lib
	ar rcs $@ $^

examples: lib/libmsptools.a
	$(MAKE) --directory=examples

test: lib/libmsptools.a
	$(MAKE) --directory=tests

clean:
	-$(RM) src/*.o lib/libmsptools.a
	-$(RM) data/*_copy.txt
	$(MAKE) --directory=examples clean
	$(MAKE) --directory=tests clean

