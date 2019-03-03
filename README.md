# jfifo

This is a circular byte buffer that encodes the state of the buffer using integer values "added" and "removed."
These stor total number of bytes added and removed all other information needed to add or remove data can be derived from these two values. 

## Features of this implementaion:
  * No lost bytes: buffer can hold exactly "capacity" bytes with no compromise
  * Thread safe single direction transfer.* Data can be added without modifying removed, removed without modifying added.
  * Records total added/removed(up to max value of index_type)
  * All non constant variables are initialized to zero

*assuming that JFIFO_INDEX_TYPE is set to a type(default unsigend int) that is atomic on the target platfrom. Unsigned int is not garunteed to be atomic by any ANSI C standard, but it pretty much always is. You can chaged the type by setting the JFIFO_INDEX_TYPE macro when compileing.[see](https://www.gnu.org/software/libc/manual/html_node/Atomic-Types.html)

### Prerequisites
ANSI C compiler.


