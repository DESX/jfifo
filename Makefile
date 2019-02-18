all:test0.exe

CC:=gcc

MAKEFLAGS:= -s

test0.o:jfifo.h jfifo.o

CFLAGS:=-std=gnu99 -Wall -Wextra -Wpedantic -DTEST_MODE

%.exe: %.o jfifo.o
	$(LINK.o) $^	 $(LOADLIBES) $(LDLIBS) -o $@



clean:
	rm -f test0.exe
	rm -f *.o
