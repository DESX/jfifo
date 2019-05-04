# jfifo
Simple fixed-size first-in-first-out circular byte buffer.  
## usage
```c
   #include "jfifo.h"
   
   //create the buffer
   char data[12];
   jfifo_t fifo = {data, sizeof(data), 0, 0};
   
   //add some date
   char to_add = 'c';
   jfifo_add_byte(&fifo, &to_add);
   
   //get some data back
   char to_remove;
   int removed = jfifo_remove_byt(&fifo, &to_remove);
   if(removed == 1)
   {
      printf("removed: %c\n",to_remove);
   }
```
## Features:
  * No lost bytes: buffer can hold exactly "capacity" bytes with no compromise
  * Thread safe single direction transfer*
  * Records total added/removed 
  * All non constant variables are initialized to zero

*assuming that JFIFO_INDEX_TYPE is set to a type (default unsigend int) that is atomic on the target platfrom. Unsigned int is not guaranteed to be atomic by any ANSI C standard, [but it pretty much always is](https://www.gnu.org/software/libc/manual/html_node/Atomic-Types.html). You can chage the type by setting the JFIFO_INDEX_TYPE macro when compileing. 

### Prerequisites
ANSI C compiler.


