#ifndef JFIFO_H
#define JFIFO_H
typedef struct jfifo
{
   void * data;
   unsigned int len;
   unsigned int added;
   unsigned int removed;
}jfifo;
#endif
