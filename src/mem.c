#include "mem.h"
#include "base.h"
#include "exception_handling.h"

void safe_memcpy(
    void* dest,
    const void* src,
    size_t bytes)
{
  ASSERT(dest);
  ASSERT(src);
  ASSERT(bytes > 0);
  for (size_t i = 0; i < bytes; ++i)
    ((uint8_t*)dest)[i] = ((uint8_t*)src)[i];
}

void zero(void* input, size_t bytes)
{
  uint8_t* data = input;
  for (size_t i = 0; i < bytes; ++i) {
    data[i] = 0;
  }
}

mem_arena mem_arena_init(size_t capacity)
{
  mem_arena ret = {
    .capacity = capacity,
    .ind = 0,
    .data = malloc(capacity)
  };
  RUNTIME_CHECK(ret.data != NULL, "Failed to allocate memory for memory arena");
  return ret;
}

void* mem_arena_malloc_kill(mem_arena* a, size_t len)
{
  ASSERT(a);
  ASSERT(len > 0);

  RUNTIME_CHECK(a->ind + len <= a->capacity, "Out of memory for mem arena");

  void* ret = &((uint8_t*)a->data)[a->ind];
  a->ind += len;
  return ret;
}

void mem_arena_push_byte_kill(mem_arena* a, uint8_t b)
{
  ASSERT(a);

  RUNTIME_CHECK(a->ind + 1 <= a->capacity, "Out of memory for mem arena");

  ((uint8_t*)a->data)[a->ind++] = b;
}

void* mem_arena_head(mem_arena* a)
{
  return &((uint8_t*)a->data)[a->ind];
}

void mem_arena_free(mem_arena* a)
{
  ASSERT(a);
  ASSERT(a->data);
  log_debugln("Freeing memory arena. You used: %zu bytes of %zu bytes.", a->ind, a->capacity);
  free(a->data);
  a->capacity = 0;
  a->ind = 0;
  a->data = 0;
}
