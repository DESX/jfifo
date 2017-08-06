#include <stdio.h>
#include <limits.h>
#include "jfifo.h"


JFIFO_CREATE(f0, 10);
JFIFO_CREATE(f1, 11);
JFIFO_CREATE(f2, 12);
JFIFO_CREATE(f3, 13);

int main(int argc __attribute__ ((unused)), char ** argv __attribute__ ((unused)))
{
   printf("starting jfifo test 1\n");
   printf("rollover: %u r %u\n", jfifo_rollover(&f0)/f0.len,jfifo_rollover(&f0)%f0.len);
   printf("rollover: %u r %u\n", jfifo_rollover(&f1)/f1.len,jfifo_rollover(&f1)%f1.len);
   printf("rollover: %u r %u\n", jfifo_rollover(&f2)/f2.len,jfifo_rollover(&f2)%f2.len);
   printf("rollover: %u r %u\n", jfifo_rollover(&f3)/f3.len,jfifo_rollover(&f3)%f3.len);
   for(unsigned int i = 0;i < UINT_MAX;i++)
   {
      if( ~i == (UINT_MAX - i))
      {
      }
      else
      {
         printf("fail %u\n",i);
      }
      if(! (i%0xfffffff))printf("x%u\n",i);
   }
   printf("test complete\n");
   
}
