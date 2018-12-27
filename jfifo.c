#include "jfifo.h"

#if 0
j_cnt jfifo_rollover(jfifo * t)
{
   j_cnt len_inv = ~t->cap + 1;
   return len_inv - (len_inv % t->cap);
}

j_cnt jfifo_max_capacity()
{
   return (1 << SHIFT_WIDTH(j_cnt));
}

j_cnt jfifo_population(jfifo * t)
{
   j_cnt population = t->added - t->removed; 

   population += jfifo_rollover(t) * (population >> SHIFT_WIDTH(j_cnt));

   return population;
}

j_cnt jfifo_add_byte(jfifo * t, char byte)
{
   if(jfifo_population(t) < t->cap)
   {
      j_cnt add_index = t->added % t->cap;   

      t->data[add_index] = byte;

      t->added = (t->added + 1) % jfifo_rollover(t);
   }
   return 1;
}

char * jfifo_remove_byte(jfifo * t)
{
   char * val = NULL;

   if(jfifo_population(t) > 0)
   {
      j_cnt remove_index = t->removed % t->cap;   

      val = t->data + remove_index; 

      t->removed = (t->removed + 1) % jfifo_rollover(t);
   }

   return val;
}
#endif
