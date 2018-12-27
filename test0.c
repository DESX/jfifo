#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include "jfifo.h"
#if 0
int jfifo_check()
{

   j_cnt capacity = 0;
   j_cnt start = 0;

   do
   {

      do
      {
         JFIFO_TEST_CREATE(t, capacity, start);

         j_cnt total_added = 0;

         while(1)
         {
            j_cnt added = jfifo_add_byte(&t, 99); 

            if(added > 0)
            {
               total_added++; 
            }
            else
            {
               break;
            }
         }

         j_cnt total_removed = 0;

         while(1)
         {
            char * removed = jfifo_remove_byte(&t); 

            if(removed != NULL)
            {
               total_removed ++;
            }
            else
            {
               break;
            }
         }
         
         start++;

      }while (start != 0);

      capacity++;

   }while (capacity != jfifo_max_capacity());

   return 0;
}
#endif



int main()
{
   //jfifo_check();
   printf("starting jfifo test 1\n");
}
