#include "jfifo.h"
#include <stdio.h>



//Naming conventions:
//1. nose : byte that will be written to the next time a byte is added (initially index zero)  
//2. head : byte that is behind* nose index (initially index capacity - 1)
//3. rear : byte that will be removed from the buffer next time a byte is removed (initially zero)
//4. tail : byte that is behind the rear index (initially capacity - 1)
//5. population: number of bytes on the buffer
//6. vacancies: number of bytes on the buffer
//
//*behind mean "less than includeing wraping"
//if the buffer size is 10:,
//byte index 0 is behind index 1
//byte index 9 is behind index 0


//rollover explained
//an obvious challenge to using continuously incremented index values is the rollover
//its a big problem if after adding 4.2 billion values to your buffer, adding more values corrupts memory 
//to deal with this, all operations on added and removed preserve the integrity even when one or both
//buffers reach their maximum value
//not that by the ANSI c standard, unsigend integers are garunteed to evaluate to the modul of the overflow.
//for instance: 
//UINT_MAX + 1 = 0
//UINT_MAX + 2 = 1
//
//the rollover is the highest possible multiple of len that is less than or 
//equal to (UINT_MAX - len)
//
//the three specific requirements here are:(inifinite precision assumed):
//
//0: ((rollover - 1) + len) <= UINT_MAX
//1: ((rollover - 1) + (len*2)) > UINT_MAX
//2: (rollover % len) == 0
//
//NOTE: (rollover - 1) is the max possible value of added/removed
//len is the max possible value that will be added to added/removed
//if the sum is larger that UINT_MAX "undefined behavior" will occure
//
//Axiom 1:
//let A be an unsigned integer encoded with a finite number of bits
//~A == (UINT_MAX - A)
//
//Axiom 2:
//let B and A be and unsigned ints where B > A > 0
//B - A < B
//
//Axiom 3:
//let B and A be and unsigned ints where B > A > 0
//(B % A) <= B - A  
//
//Axiom 4:
//let B and A be and unsigned ints where B > 0
//(A % B) <  B 
//
//len > 0 and len <= INT_MAX/2
//
//criteria 0 
//rollover - 1 + len <= UINT_MAX
//isolate rollover on the left:
//rollover <= UINT_MAX - len + 1
//apply axim 1:
//rollover <= ~len + 1
//therefore "len_inv" as defined in the rollover represents an inital upper bound for
//the final value of rollover
//
//if len <= INT_MAX/2 and len > 0
//UINT_MAX - len + 1 
//UINT_MAX - INT_MAX/2 + 1 = UINT_MAX/2 + 2 
//UINT_MAX - 1 + 1 = UINT_MAX
//
//(because len > 0) and len (<= UINT_MAX/2)
//len_inv >= UINT_MAX/2 + 2  and len_inv <= UINT_MAX and
//
//thus len_inv > len > 0
//apply axium 2:
//(len_inv % len) < len_inv
//
//thus the returned values is less the len_inv
//this proves that the return values meets criteria 0
//

static j_cnt jfifo_rollover(jfifo_t * t)
{
   j_cnt len_inv = ~t->capacity + 1;
   return len_inv - (len_inv % t->capacity);
}

size_t jfifo_vacancies(jfifo_t * t)
{
   return t->capacity - jfifo_population(t); 
}

size_t jfifo_population(jfifo_t * t)
{
   j_cnt population = t->added - t->removed; 

   if(t->added < t->removed)
   {
      population += jfifo_rollover(t);
   }

   return population;
}

size_t jfifo_add_byte(jfifo_t * t, char * byte)
{
   if(byte == NULL) return 0;

   if(jfifo_population(t) < t->capacity)
   {
      j_cnt add_index = t->added % t->capacity;   

      t->data[add_index] = *byte;

      t->added = (t->added + 1) % jfifo_rollover(t);

      return 1;
   }
   return 0;
}

size_t jfifo_remove_byte(jfifo_t * t, char * val)
{
   int bytes_removed = 0;

   if(jfifo_population(t) > 0)
   {
      j_cnt remove_index = t->removed % t->capacity;   

      *val = t->data[remove_index]; 

      t->removed = (t->removed + 1) % jfifo_rollover(t);

      bytes_removed ++;
   }

   return bytes_removed;
}

