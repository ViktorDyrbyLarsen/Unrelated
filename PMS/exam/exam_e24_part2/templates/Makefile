CC=gcc
CPPFLAGS=
CFLAGS=-Wall -Wextra -std=c11
LDLIBS=-lm
LDFLAGS=

EXAM=exam_e24

.PHONY: all handin clean

all: $(EXAM)_q1.o $(EXAM)_q2.o $(EXAM)_q3a.o $(EXAM)_q3b.o

handin: $(EXAM)_q1.c $(EXAM)_q2.c $(EXAM)_q3a.c $(EXAM)_q3b.c
	tar -cvf $(EXAM)_handin.tar $^

test_q1: $(EXAM)_q1.o
test_q2: $(EXAM)_q2.o
test_q3a: $(EXAM)_q3a.o
test_q3b: $(EXAM)_q3b.o

clean:
	-$(RM) *.o $(EXAM)_handin.tar test_q1 test_q2 test_q3a test_q3b

	