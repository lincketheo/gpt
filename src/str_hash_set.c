#include "str_hash_set.h"
#include "mem.h"
#include "exception_handling.h"

#include <sys/types.h>

void str_hash_set_init(str_hash_set shs)
{
  zero(shs.entries, shs.len * sizeof(string*));
}

static ssize_t get_avail_ind(const str_hash_set shs, const string str)
{
  ASSERT(str.len != 0);
  size_t ind = hash_func(str) % shs.len;
  size_t start = ind;
  while (shs.entries[ind].len != 0) {
    if (strequal(str, shs.entries[ind]))
      return -1;
    ind = (ind + 1) % shs.len;
    RUNTIME_CHECK(ind != start, "Hash table ran out of size");
  }
  return ind;
}

void str_hash_set_set(str_hash_set shs, const string str)
{
  ssize_t ind = get_avail_ind(shs, str);
  if (ind == -1)
    return;
  shs.entries[ind] = str;
}

int str_hash_set_contains(const str_hash_set shs, const string str)
{
  return get_avail_ind(shs, str) == -1;
}
