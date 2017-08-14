.PHONY:TMP

TMP:test0.exe

all:TMP

CC:=gcc


test0.o:jfifo.h

%.exe: %.o
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@
	./$@

CFLAGS:=-std=gnu99 -Wall -Wextra -Wpedantic


clean:
	rm -f test0.exe
