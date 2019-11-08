
// Martti Aukia 51657228
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
  bool allocated;  // replaced with bool
  void* start;
  size_t size;
  struct segmentdescriptor* next;
} Segment_t;

// point to the list of segment descriptors.
extern Segment_t* segmenttable;  // use of reserved type naming
                                 // convention '_t'-postfix

/******************** my own helper functions for readability ********************/
_Bool isFree(Segment_t*, size_t);
Segment_t seg_get(_Bool, void*, size_t, Segment_t*);
/********************            end                          ********************/

// forward references, user interface

// this function initialises the segmentation table and the memory array, it has
void initialize();
void* mymalloc(size_t);
void myfree(void*);
void mydefrag(void**);

// forward references, managing segmentation table
Segment_t* findFree(Segment_t*, size_t);
void insertAfter(Segment_t*, Segment_t*);

// forward references, helper functions
int isPrintable(int c);
void printmemory();
void printsegmenttable();

#endif