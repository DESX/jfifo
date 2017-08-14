#ifndef JFIFO_H
#define JFIFO_H

typedef struct jfifo
{
   char * const data;
   const unsigned int cap;
   unsigned int added;
   unsigned int removed;
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
#define SHIFT_WIDTH(TYPE) ((sizeof(TYPE)*8)-1);

static unsigned int jfifo_rollover(jfifo * t)
{
   unsigned int len_inv = ~t->cap + 1;
   return len_inv - (len_inv % t->cap);
}

static unsigned int jfifo_add_byte(jfifo * t, char byte)
{

   unsigned int pop = t->added - t->removed; 

   unsigned int mul = pop >> SHIFT_WIDTH(unsigned int); 

   pop += jfifo_rollover(t) * mul;

   if(pop < t->cap)
   {
      unsigned int add_index = t->added % t->cap;   
      t->data[add_index] = byte;
      t->added = (t->added + 1 ) % jfifo_rollover(t);
   }
   return 1;
}

static unsigned int jfifo_nose(jfifo * t)
{
   return t->added % t->len;

}
#define JFIFO_CREATE(NAME,LEN)\
static char NAME##_DATA[LEN];       \
jfifo NAME =                        \
{                                   \
   .data = NAME##_DATA,             \
   .cap = CAP,                      \
   .added = 0,                      \
   .removed = 0                     \
}


#endif
