
//////////////////////////////////
////////////// Section: Safe memory functions
void safe_memcpy(
    void* dest,
    const void* src,
    unsigned int bytes);

void zero(void* input, unsigned int bytes);

//////////////////////////////////
////////////// Section: Memory Arena
typedef struct {
  void* data;
  unsigned int ind;
  unsigned int capacity;
} mem_arena;

mem_arena mem_arena_init(unsigned int capacity);

void* mem_arena_malloc(mem_arena* a, unsigned int len);

void mem_arena_free(mem_arena* a);

//////////////////////////////////
////////////// Malloc Behaviors
typedef enum {
  FAIL_ABORT,
  RET_NULL,
} alloc_behavior;
