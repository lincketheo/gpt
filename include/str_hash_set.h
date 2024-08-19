#include "str_utils.h"
#include <sys/types.h>

typedef struct {
  string* entries;
  const size_t len;
} str_hash_set;

void str_hash_set_init(str_hash_set shs);

void str_hash_set_set(str_hash_set shs, const string str);

int str_hash_set_contains(const str_hash_set shs, const string str);

