#ifndef JFIFO_H
#define JFIFO_H

typedef struct jfifo
{
   const char * data;
   const unsigned int len;
   unsigned int added;
   unsigned int removed;
}jfifo;

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
