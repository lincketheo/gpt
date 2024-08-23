#include "bit_set.h"
#include "exception_handling.h"
#include "mem.h"

void bit_hash_set_init(bit_hash_set bhs)
{
  zero(bhs.data, bhs.byte_len);
}

void bit_hash_set_set(bit_hash_set* bhs, unsigned int bit_index)
{
  ASSERT(bit_index <= 8 * bhs->byte_len);
  bhs->data[bit_index / 8] |= (1 << (7 - bit_index % 8));
}

int bit_hash_set_get(const bit_hash_set* bhs, unsigned int bit_index)
{
  ASSERT(bit_index <= 8 * bhs->byte_len);
  return bhs->data[bit_index / 8] & (1 << (7 - bit_index % 8));
}
