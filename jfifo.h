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

#define JFIFO_CREATE(NAME, CAP) \
char NAME##_DATA[CAP];   \
jfifo NAME =             \
{                               \
   .data = NAME##_DATA,         \
   .cap = CAP,                  \
   .added = 0,                  \
   .removed = 0                 \
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
