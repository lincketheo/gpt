#include "mem.h"
#include "exception_handling.h" // ASSERT

#include <stdlib.h> // malloc

void safe_memcpy(
    void* dest,
    const void* src,
    unsigned int bytes)
{
  ASSERT(dest);
  ASSERT(src);
  ASSERT(bytes > 0);
  for (unsigned int i = 0; i < bytes; ++i)
    ((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
}

void zero(void* input, unsigned int bytes)
{
  unsigned char* data = input;
  for (unsigned int i = 0; i < bytes; ++i) {
    data[i] = 0;
  }
}

mem_arena mem_arena_init(unsigned int capacity)
{
  mem_arena ret = {
    .capacity = capacity,
    .ind = 0,
    .data = malloc(capacity)
  };
  RUNTIME_CHECK(ret.data != NULL, "Failed to allocate memory for memory arena");
  return ret;
}

void* mem_arena_malloc(mem_arena* a, unsigned int len)
{
  ASSERT(a);
  ASSERT(len > 0);

  RUNTIME_CHECK(a->ind + len <= a->capacity, "Out of memory for mem arena");

  void* ret = &((unsigned char*)a->data)[a->ind];
  a->ind += len;
  return ret;
}

void mem_arena_free(mem_arena* a)
{
  ASSERT(a);
  ASSERT(a->data);
  log_debugln("Freeing memory arena. "
              "You used: %d bytes of %d bytes.",
      a->ind, a->capacity);
  free(a->data);
  a->capacity = 0;
  a->ind = 0;
  a->data = 0;
}
