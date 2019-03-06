all:test0.exe

CC:=cc

#MAKEFLAGS:= -s

test0.o:jfifo.h jfifo.o

CFLAGS:=-std=c11 -Wall -Wextra -Wpedantic -DTEST_MODE
CPPFLAGS:= -D'JFIFO_INDEX_TYPE=unsigned char'

%.exe: %.o jfifo.o
	$(LINK.o) $^	 $(LOADLIBES) $(LDLIBS) -o $@

clean:
	rm -f test0.exe
	rm -f *.o
