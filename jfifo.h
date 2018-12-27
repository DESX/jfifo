#ifndef JFIFO_H
#define JFIFO_H

typedef struct
{
   char * const data;
   const unsigned int max_capacity;
   unsigned int added_count;
   unsigned int removed_count;
}jfifo_t;

//this is a circular byte buffer class that encodes the entire state of the buffer using only two non constant variables "added" and "removed"
//these do exactly what their names imply: the total number of bytes added and removed
//all other information needed to add or remove data can be derived from these two values:
//1. nose index: index of byte that will be written to the next time a byte is added (initially zero)  
//2. head index: index of byte that is behind* nose index (initially max_capacity - 1)
//3. rear index: index of byte that will be removed from the buffer next time a byte is removed (initially zero)
//4. tail index: index of byte that is behind the rear index (initially max_capacity - 1)
//5. population: number of bytes on the buffer
//*behind refers to the index that is on less

//The wording of the above descritions are very intentional
//"the next time" a byte is added or removed means that this value

//Features of this implementaion:
//1. No lost bytes: buffer can hold exactly "capacity" bytes with no compromise
//2. Thread safe single direction transfer: Data can be added without modifying removed, removed without modifying added
//3. Records total added/removed
//4. All non constant variables are initialized to zero
//5. 

//the rollover is the highest possible multiple of len that is less than or 
//equal to (UINT_MAX - len)
//
//the three specific requirements here are:(inifinite precision assumed):
//
//0: ((rollover - 1) + len) <= UINT_MAX
//1: ((rollover - 1) + (len*2)) > UINT_MAX
//2: (rollover % len) == 0
//
//NOTE: (rollover - 1) is the max possible value of added/removed
//len is the max possible value that will be added to added/removed
//if the sum is larger that UINT_MAX "undefined behavior" will occure
//
//Axiom 1:
//let A be an unsigned integer encoded with a finite number of bits
//~A == (UINT_MAX - A)
//
//Axiom 2:
//let B and A be and unsigned ints where B > A > 0
//B - A < B
//
//Axiom 3:
//let B and A be and unsigned ints where B > A > 0
//(B % A) <= B - A  
//
//Axiom 4:
//let B and A be and unsigned ints where B > 0
//(A % B) <  B 
//
//len > 0 and len <= INT_MAX/2
//
//criteria 0 
//rollover - 1 + len <= UINT_MAX
//isolate rollover on the left:
//rollover <= UINT_MAX - len + 1
//apply axim 1:
//rollover <= ~len + 1
//therefore "len_inv" as defined in the rollover represents an inital upper bound for
//the final value of rollover
//
//if len <= INT_MAX/2 and len > 0
//UINT_MAX - len + 1 
//UINT_MAX - INT_MAX/2 + 1 = UINT_MAX/2 + 2 
//UINT_MAX - 1 + 1 = UINT_MAX
//
//(because len > 0) and len (<= UINT_MAX/2)
//len_inv >= UINT_MAX/2 + 2  and len_inv <= UINT_MAX and
//
//thus len_inv > len > 0
//apply axium 2:
//(len_inv % len) < len_inv
//
//thus the returned values is less the len_inv
//this proves that the return values meets criteria 0
//

#define JFIFO_CREATE(NAME, CAP)  \
char NAME##_DATA[CAP];           \
jfifo NAME =                     \
{                                \
   .data = NAME##_DATA,          \
   .cap = CAP,                   \
   .added = 0,                   \
   .removed = 0                  \
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
