#pragma once

typedef struct {
  unsigned char* data;
  unsigned int byte_len;
} bit_hash_set;

void bit_hash_set_init(bit_hash_set bhs);

void bit_hash_set_set(bit_hash_set* bhs, unsigned int bit_index);

int bit_hash_set_get(const bit_hash_set* bhs, unsigned int bit_index);
