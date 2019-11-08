#ifndef MEMALLOC_H
#define MEMALLOC_H

#include <stdlib.h>

#define MAXMEMORY 1024

typedef struct segment {
  int start;
  int size;
  int status;
  struct segment* next;
  struct segment* prev;
} segment_t;

segment_t* mem_alloc(int);
void mem_free(segment_t*);

#endif