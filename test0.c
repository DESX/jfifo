#include <stdio.h>
#include <limits.h>
#include "jfifo.h"

JFIFO_CREATE(f0, 10);

#define NOUSED __attribute__ ((unused))

int main(int argc NOUSED , char ** argv NOUSED)
{
   jfifo_add_byte(&f0,10);

   printf("starting jfifo test 1\n");
   printf("rollover: %u\n", jfifo_rollover(&f0));
}
