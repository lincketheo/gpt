#include "random_utils.h"
#include <stdlib.h>

#define rand_arr_decl_impl(type, suffix)           \
  rand_arr_decl(type, suffix)                      \
  {                                                \
    for (unsigned int i = 0; i < len; ++i) {       \
      buffer[i] = rand_v(type, suffix)(low, high); \
    }                                              \
  }

rand_decl(float, f32)
{
  return low + ((float)rand() / RAND_MAX) * (high - low);
}

rand_arr_decl_impl(float, f32)
