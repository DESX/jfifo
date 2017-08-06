#ifndef JFIFO_H
#define JFIFO_H

typedef struct jfifo
{
   const char * data;
   const unsigned int len;
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
//the folowing is a general rule:
//let A be an unsigned int (limited precision assumed)
//~A == (UINT_MAX - A)
//A -  
static unsigned int jfifo_rollover(jfifo * t)
{
   unsigned int len_inv = ~t->len + 1;
   return len_inv - (len_inv % t->len);
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
   .len = LEN,                      \
   .added = 0,                      \
   .removed = 0                     \
}


#endif
