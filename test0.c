#include <stdio.h>
#include "jfifo.h"


JFIFO_CREATE(f0,10);

int main(int argc __attribute__ ((unused)), char ** argv __attribute__ ((unused)))
{
   printf("starting jfifo test 1\n");
   printf("rollover: %lu\n", jfifo_rollover(&f0));
   
}
