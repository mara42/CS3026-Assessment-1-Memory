#include <stdio.h>
#include <string.h>
#include "mymemory.h"
#include "mymemory.c"

int main() {
  printf("shell> start\n");

  initialize();

  printmemory();
  printsegmenttable();

  printf("shell> end\n");

  return 0;
}