#ifndef JFIFO_H
#define JFIFO_H

typedef struct jfifo
{
   char * const data;
   const unsigned int cap;
   unsigned int added;
   unsigned int removed;
}jfifo;

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

#define JFIFO_CREATE(NAME,CAP)\
static char NAME##_DATA[CAP];       \
jfifo NAME =                        \
{                                   \
   .data = NAME##_DATA,             \
   .cap = CAP,                      \
   .added = 0,                      \
   .removed = 0                     \
}


#endif
