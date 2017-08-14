#ifndef JFIFO_H
#define JFIFO_H

typedef unsigned char j_cnt;
typedef struct jfifo
{
   char * const data;
   const j_cnt cap;
   j_cnt added;
   j_cnt removed;
}jfifo;

//the rollover is the highest possible multiple of len that is less than or 
//equal to UINT_MAX - len
//
//the three specific requirement here is this(inifinite precision assumed):
//
//0: (rollover - 1) + len <= UINT_MAX
//1: (rollover - 1) + len*2 > UINT_MAX
//2: (rollover % len) == 0
//
//NOTE: (rollover - 1) is the max possible value of added/removed
//len is the max possible value that will be added to added/removed
//if the sum is larger that UINT_MAX "undifined behavior" will occure
//
//axiums:
//
//axium 1:
//let A be an unsigned int (limited precision assumed)
//~A == (UINT_MAX - A)
//
//axium 2:
//let B and A be and unsigned ints where B > A > 0
//
//axium 3:
//let B and A be and unsigned ints where B > A > 0
//B - A < B
//
//
//(B % A) <= B - A  
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
//because len > 0 and len <= UINT_MAX/2
//len_inv >= UINT_MAX/2 + 2  and len_inv <= UINT_MAX and
//
//thus len_inv > len > 0
//apply axium 2:
//(len_inv % len) < len_inv
//
//thus the returned values is less the len_inv
//this proves that the return values meets criteria 0
//
#define SHIFT_WIDTH(TYPE) ((sizeof(TYPE)*8)-1)

static j_cnt jfifo_rollover(jfifo * t)
{
   j_cnt len_inv = ~t->cap + 1;
   return len_inv - (len_inv % t->cap);
}

static j_cnt jfifo_max_capacity()
{
   return (1 << SHIFT_WIDTH(j_cnt));
}

static j_cnt jfifo_population(jfifo * t)
{
   j_cnt population = t->added - t->removed; 

   population += jfifo_rollover(t) * (population >> SHIFT_WIDTH(j_cnt));

   return population;
}

static j_cnt jfifo_add_byte(jfifo * t, char byte)
{
   if(jfifo_population(t) < t->cap)
   {
      j_cnt add_index = t->added % t->cap;   

      t->data[add_index] = byte;

      t->added = (t->added + 1) % jfifo_rollover(t);
   }
   return 1;
}

static char * jfifo_remove_byte(jfifo * t)
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

#define JFIFO_CREATE(NAME, CAP)  \
char NAME##_DATA[CAP];           \
jfifo NAME =                     \
{                                \
   .data = NAME##_DATA,          \
   .cap = CAP,                   \
   .added = 0,                   \
   .removed = 0                  \
}

#define JFIFO_TEST_CREATE(NAME, CAP,START) \
char NAME##_DATA[CAP];           \
jfifo NAME =                     \
{                                \
   .data = NAME##_DATA,          \
   .cap = CAP,                   \
   .added = START,               \
   .removed = START              \
}


#endif
