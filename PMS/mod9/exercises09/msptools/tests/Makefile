CC=gcc
CPPFLAGS=-I../include
CFLAGS=-Wall -g -std=c99
LDFLAGS=
LDLIBS=-lm
TESTCASES=$(basename $(wildcard *test*.c))

.PHONY: run clean

run: $(TESTCASES)
	bash -c 'for val in $(TESTCASES); do echo "* Test: $$val"; ./$$val > $$val.log || echo ">>> Test failed <<<"; done'

$(TESTCASES):  ../lib/libmsptools.a

clean:
	-$(RM) $(TESTCASES)
	-$(RM) -r *_test*.dSYM
	-$(RM) *.log
