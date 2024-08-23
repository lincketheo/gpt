#include "hash_set.h"
#include "bit_set.h"
#include "str_hash_set.h"

void hash_set_init(hash_set hs, int type) {
  if(type == 0) {
    bit_hash_set_init(hs.bhs);
  } else if (type == 1) {
    str_hash_set_init(hs.shs);
  }
  ASSERT(0 && "hash set can be 0 or 1");
}

void hash_set_set(hash_set hs, const string str) {
  if(hs.type == 0) {
    bit_hash
  }
}

int hash_set_contains(const hash_set shs, const string str);

