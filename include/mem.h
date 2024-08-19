#include <stdlib.h>
#include <stdint.h>

void safe_memcpy(
    void* dest,
    const void* src,
    size_t bytes);

void zero(void* input, size_t bytes);

typedef struct {
  void* data;
  size_t ind;
  size_t capacity;
} mem_arena;

mem_arena mem_arena_init(size_t capacity);

void* mem_arena_malloc_kill(mem_arena* a, size_t len);

void mem_arena_push_byte_kill(mem_arena* a, uint8_t b);

void* mem_arena_head(mem_arena* a);

void mem_arena_free(mem_arena* a);
