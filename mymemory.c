/* mymemory.c
 *
 * provides interface to memory management
 *
 */
#include "mymemory.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// our memory
Byte mymemory[MAXMEM];
Segment_t* segmenttable = NULL;

Segment_t seg_get(_Bool allocated, void* start, size_t size, Segment_t* next) {
  Segment_t seg = {
      .allocated = allocated, .start = start, .size = size, .next = next};
  return seg;
}

void initialize() {
  printf("initialize> start\n");

  memset(mymemory, 0, MAXMEM);
  segmenttable = malloc(sizeof(Segment_t));
  *segmenttable = seg_get(FALSE, &mymemory[0], MAXMEM, 0);

  printf("initialize> end\n");
}

_Bool isFree(Segment_t* seg, size_t amount) {
  return (!(seg->allocated) && seg->size >= amount);
}

// helper functions for management segmentation table
Segment_t* findFree(Segment_t* list, size_t size) {
  printf("findFree> start\n");
  Segment_t* s = list;
  do {
    if (isFree(s, size))
      return s;
  } while ((s = segmenttable->next));
  return 0;
}

void insertAfter(Segment_t* oldSegment, Segment_t* newSegment) {
  Segment_t* last = oldSegment->next ? oldSegment->next : 0;
  oldSegment->next = newSegment;
  newSegment->next = last;
}

// this function “allocates” memory of a particular size and returns a pointer
void* mymalloc(size_t size) {
  printf("mymalloc> start\n");
  // implement the mymalloc functionality
  Segment_t* oldSegment = findFree(segmenttable, size);
  if (oldSegment) {
    oldSegment->size -= size;
    Segment_t* newSegStart = oldSegment->start;
    oldSegment->start += size;
    Segment_t* newSegment = malloc(sizeof(Segment_t));
    *newSegment = seg_get(TRUE, newSegStart, size, 0);
    insertAfter(oldSegment, newSegment);
    return newSegment->start;
  } else {
    return 0;
  }
}

void mydefrag(void** ptrlist) {
  printf("mydefrag> start\n");
}

// This function searches for a segment in the list where list->start == ptr
// This function either returns a pointer to a found segment descriptor,
// or NULL if no such segment exists
Segment_t* findSegment(Segment_t* list, void* ptr) {
  Segment_t* s = list;
  do {
    if (s->start == ptr)
      return s;

  } while ((s = s->next));

  return 0;
}

void myfree(void* ptr) {
  printf("myfree> start\n");
  Segment_t* seg = findSegment(segmenttable, ptr);
  seg->allocated = FALSE;
}

int isPrintable(int c) {
  if (c >= 0x20 && c <= 0x7e)
    return c;

  return 0;
}

void printmemory() {
  unsigned char* array = mymemory;
  char byte_buffer[16 * 3 + 1] = {0};
  char string_buffer[16 + 1] = {0};

  char format_str[] = "%03zX0  %s |%s|\n";
  size_t padding = (16 - (MAXMEM % 16)) % 16;  // mod for handling padding==16
  size_t row = 0, column = 0, byteI = 0;

  for (size_t i = 0; i < MAXMEM; i++, column++) {
    if (column == 16) {
      printf(format_str, row++, byte_buffer, string_buffer);
      column = 0;
      byteI = 0;
    }

    sprintf(byte_buffer + byteI, "%02X ", array[i]);
    byteI += 3;

    char ch = isPrintable(array[i]) ? array[i] : '.';
    sprintf(string_buffer + column, "%c", ch);
  }

  for (size_t i = 0; i < padding * 3; i++) {
    byte_buffer[byteI + i] = ' ';
  }
  printf(format_str, row++, byte_buffer, string_buffer);
}

void printsegmentdescriptor(Segment_t* descriptor) {
  printf("%c", descriptor->allocated);
  printf("\tallocated = %s\n",
         (descriptor->allocated == FALSE ? "FALSE" : "TRUE"));
  printf("\tstart     = %p\n", descriptor->start);
  printf("\tsize      = %lu\n", descriptor->size);
}

void printsegmenttable() {
  Segment_t* s = segmenttable;
  size_t i = 0;
  do {
    printf("Segment %zu\n", i++);
    printsegmentdescriptor(s);
  } while ((s = s->next));
}
