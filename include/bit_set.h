#include <stdint.h>
#include <sys/types.h>

typedef struct {
  uint8_t* data;
  size_t byte_len;
} bit_hash_set;

void bit_hash_set_init(bit_hash_set* bhs);

void bit_hash_set_set(bit_hash_set* bhs, size_t bit_index);

int bit_hash_set_get(const bit_hash_set* bhs, size_t bit_index);
