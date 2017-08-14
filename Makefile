

all:test0.exe

CC:=gcc


test0.o:jfifo.h

CFLAGS:=-std=gnu99 -Wall -Wextra -Wpedantic

%.exe: %.o
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@



clean:
	rm -f test0.exe
	rm -f *.o
