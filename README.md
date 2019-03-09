# jfifo
Simple fixed-size first-in-first-out circular byte buffer.  
## usage
```c
   char data[12];
   jfifo_t fifo = {data,sizeof(data),0,0};
```
## Features of this implementaion:
  * No lost bytes: buffer can hold exactly "capacity" bytes with no compromise
  * Thread safe single direction transfer.* Data can be added without modifying removed, removed without modifying added.
  * Records total added/removed(up to max value of index_type)
  * All non constant variables are initialized to zero

*assuming that JFIFO_INDEX_TYPE is set to a type(default unsigend int) that is atomic on the target platfrom. Unsigned int is not garunteed to be atomic by any ANSI C standard, [but it pretty much always is](https://www.gnu.org/software/libc/manual/html_node/Atomic-Types.html). You can chaged the type by setting the JFIFO_INDEX_TYPE macro when compileing.

### Prerequisites
ANSI C compiler.


