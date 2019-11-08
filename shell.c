#include <stdio.h>
#include <string.h>
#include "mymemory.h"
#include "mymemory.c"

int main() {
  printf("shell> start\n");

  initialize();

  char* ptr1 = (char*)mymalloc(16);
  strcpy(ptr1, "this test981273");
  printf("shell> content of allocated memory: %s\n", ptr1);

  char* ptr2 = (char*)mymalloc(10);
  strcpy(ptr2, "this test");
  printf("shell> content of allocated memory: %s\n", ptr2);

  char* ptr3 = (char*)mymalloc(204);
  strcpy(ptr3, "this test del me now");
  printf("shell> content of allocated memory: %s\n", ptr2);

  printmemory();
  printsegmenttable();

  printf("shell> end\n");

  return 0;
}