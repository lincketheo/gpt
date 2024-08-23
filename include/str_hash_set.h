#pragma once

typedef struct {
  char* entries;
  const unsigned int len;
} str_hash_set;

/**
 * Encodes a string to store it in a hash table
 * encoding: [size (in [0, 255])]char,char,char
 */
int strencode(
    char* dest,
    const char* src,
    unsigned int destl,
    unsigned int srcl);

void str_hash_set_init(str_hash_set shs);

void str_hash_set_set(
    str_hash_set* shs,
    const char* str,
    unsigned int len);

int str_hash_set_contains(
    const str_hash_set shs,
    const char* str,
    unsigned int len);
