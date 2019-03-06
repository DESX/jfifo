#ifndef JFIFO_H
#define JFIFO_H

#ifndef  JFIFO_INDEX_TYPE
typedef unsigned int j_cnt;
#else
typedef JFIFO_INDEX_TYPE j_cnt;
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

size_t jfifo_add_byte(jfifo_t *, char *);
size_t jfifo_remove_byte(jfifo_t *, char *);

#endif
