#include "mem.h"
#include <stdint.h>

void zero(void* input, size_t bytes)
{
  uint8_t* data = input;
  for (size_t i = 0; i < bytes; ++i) {
    data[i] = 0;
  }
}

