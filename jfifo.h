#ifndef JFIFO_H
#define JFIFO_H

#ifdef TEST_MODE
typedef unsigned char j_cnt;
#else
typedef unsigned int j_cnt;
#endif

typedef struct
{
   char *const data;
   const size_t  capacity;
   j_cnt added;
   j_cnt removed;
}jfifo_t;

size_t jfifo_population(jfifo_t *);
size_t jfifo_vacancies(jfifo_t *);

unsigned int jfifo_add_byte(jfifo_t *, char *);
unsigned int jfifo_remove_byte(jfifo_t *, char *);

#endif
