#include "hashing.h"

unsigned int djb2_hash(const char* str, unsigned int len)
{
  unsigned int ret = 5381;
  for (unsigned int i = 0; i < len; ++i) {
    ret = ((ret << 5) + ret) + str[i];
  }
  return ret;
}
