#include <stdio.h>
#include <stdlib.h>
#include "jfifo.h"
#if 0
#include <limits.h>
#endif

#define TST_SIZE 10

int main()
{
   const unsigned int buffer_size=10;
   char data[buffer_size];
   jfifo_t fifo={data,buffer_size,0,0};

   int step = 0;
   
	char add= 0;
	char remove = 0;
	char remove_prev = -1;

	for(int i = 0; i < 1000;i++)
	{
		int cnt = 0;
      while(1)
		{
			cnt = jfifo_add_byte(&fifo, &add);
         if(cnt == 1)
            add++;
         else
            break;
		}

      if(jfifo_population(&fifo) != buffer_size)
      {
        goto fail; 
      }

      step++;
      
      while(1)
		{
			cnt = jfifo_remove_byte(&fifo, &remove);

         if(cnt == 1)
         {
            char expected = remove_prev+1;

            if(remove != expected)
            {
               printf("expected %d but got %d\n",expected,remove);
               goto fail; 
            }
            step++;

            remove_prev = remove;
         }
         else
         {
            break;
         } 
		}

      if(jfifo_population(&fifo) != 0)
      {
        goto fail; 
      }

      step++;
	}
   printf("all pass\n");
   printf("added %d\n",fifo.added);
   printf("removed %d\n",fifo.removed);
   return EXIT_SUCCESS;
fail:
   printf("test failed at step %d\n",step);
}
