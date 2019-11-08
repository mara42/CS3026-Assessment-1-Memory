/* mymemory.h
 *
 * describes structures for memory management
 */

#ifndef MYMEMORY_H
#define MYMEMORY_H

#include <stddef.h>
#include <stdbool.h>

#ifndef TRUE
#define TRUE true  // replace int with bool
#endif
#ifndef FALSE
#define FALSE false  // replace int with bool
#endif

#define MAXMEM 1024
#define MAXSEGMENTS 100

// this typedef defines a byte
typedef unsigned char Byte;

// this is our memory, we declare it as extern so that it becomes global
extern Byte mymemory[MAXMEM];

// the segment descriptor, a node in a linked list
typedef struct segmentdescriptor {
  // The attribute “allocated” represents a Boolean (in mymemory.h, the two
  // macros TRUE and FALSE are defined and should be used for “allocated”.
  bool allocated;  // replaced with bool
  // The attribute “start” points to the byte in mymemory where the allocated
  // segment starts
  void* start;
  // The attribute “size” defines the number of bytes of a segment
  size_t size;
  struct segmentdescriptor* next;
} Segment_t;

// point to the list of segment descriptors.
extern Segment_t* segmenttable;  // use of reserved type naming
                                 // convention '_t'-postfix

// forward references, user interface

// this function initialises the segmentation table and the memory array, it has
// to be called first before the other functions can be used.
void initialize();
// this function “allocates” memory of a particular size and returns a pointer
// to the first byte of the allocated segment
void* mymalloc(size_t);
// frees a previously allocated memory
void myfree(void*);
// defragments the memory and compacts smaller segments into larger ones
void mydefrag(void**);

// forward references, managing segmentation table
Segment_t* findFree(Segment_t*, size_t);
void insertAfter(Segment_t*, Segment_t*);

// forward references, helper functions
int isPrintable(int c);
void printmemory();
void printsegmenttable();

#endif