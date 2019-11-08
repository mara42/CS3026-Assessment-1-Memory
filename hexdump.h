#ifndef HEXDUMP_H
#define HEXDUMP_H

#include <stdio.h>

#define FORMAT_STR "%03zX0  %s |%s|\n"

void hexdump(void* address, size_t length) {
  unsigned char* array = address;
  char byte_buffer[16 * 3 + 1] = {0};
  char string_buffer[16 + 1] = {0};

  size_t padding = (16 - (length % 16)) % 16;  // mod for handling padding==16
  size_t row = 0, column = 0, byteI = 0;

  for (size_t i = 0; i < length; i++, column++) {
    if (column == 16) {
      printf(FORMAT_STR, row++, byte_buffer, string_buffer);
      column = 0;
      byteI = 0;
    }

    sprintf(byte_buffer + byteI, "%02X ", array[i]);
    byteI += 3;

    char ch = (array[i] > 31) ? array[i] : '.';
    sprintf(string_buffer + column, "%c", ch);
  }

  for (size_t i = 0; i < padding * 3; i++) {
    byte_buffer[byteI + i] = ' ';
  }
  printf(FORMAT_STR, row++, byte_buffer, string_buffer);
}

#endif
