#ifndef JFIFO_H
#define JFIFO_H

#ifdef TEST_MODE
typedef unsigned char j_cnt;
#else
typedef unsigned int j_cnt;
#endif

typedef struct
{
   char * data;
   unsigned int max_capacity;
   j_cnt added_count;
   j_cnt removed_count;
}jfifo_t;

unsigned int jfifo_population(jfifo_t *);
unsigned int jfifo_vacancies(jfifo_t *);

unsigned int jfifo_add_byte(jfifo_t *, char *);
unsigned int jfifo_remove_byte(jfifo_t *, char *);

#endif
