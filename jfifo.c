#include "jfifo.h"
#include <stdio.h>

//this is a circular byte buffer class that encodes the entire state of the
//buffer using only two non constant variables "added" and "removed" these do
//exactly what their names imply: the total number of bytes added and removed
//all other information needed to add or remove data can be derived from these
//two values:

//1. nose : byte that will be written to the next time a byte is added (initially index zero)  
//2. head : byte that is behind* nose index (initially index max_capacity - 1)
//3. rear : byte that will be removed from the buffer next time a byte is removed (initially zero)
//4. tail : byte that is behind the rear index (initially max_capacity - 1)
//5. population: number of bytes on the buffer
//6. vacancies: number of bytes on the buffer
//*behind refers to the index that is on less

//The wording of the above descritions are very intentional
//"the next time" a byte is added or removed means that this value

//Features of this implementaion:
//1. No lost bytes: buffer can hold exactly "capacity" bytes with no compromise
//2. Thread safe single direction transfer: Data can be added without modifying removed, removed without modifying added
//3. Records total added/removed
//4. All non constant variables are initialized to zero
//5. 

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
   j_cnt len_inv = ~t->max_capacity + 1;
   return len_inv - (len_inv % t->max_capacity);
}

unsigned int jfifo_vacancies(jfifo_t * t)
{
   return t->max_capacity - jfifo_population(t); 
}

unsigned int jfifo_population(jfifo_t * t)
{
   j_cnt population = t->added_count - t->removed_count; 

   if(t->added_count < t->removed_count)
   {
      population += jfifo_rollover(t);
   }

   return population;
}

unsigned int jfifo_add_byte(jfifo_t * t, char * byte)
{
   if(byte == NULL) return 0;

   if(jfifo_population(t) < t->max_capacity)
   {
      j_cnt add_index = t->added_count % t->max_capacity;   

      t->data[add_index] = *byte;

      t->added_count = (t->added_count + 1) % jfifo_rollover(t);

      return 1;
   }
   return 0;
}

unsigned int jfifo_remove_byte(jfifo_t * t, char * val)
{
   int bytes_removed = 0;

   if(jfifo_population(t) > 0)
   {
      j_cnt remove_index = t->removed_count % t->max_capacity;   

      *val = t->data[remove_index]; 

      t->removed_count = (t->removed_count + 1) % jfifo_rollover(t);

      bytes_removed ++;
   }

   return bytes_removed;
}

