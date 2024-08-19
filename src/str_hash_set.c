#include "str_hash_set.h"
#include "mem.h"

static size_t djb2_hash(const string str)
{
  size_t ret = 5381;
  int c;
  int i = 0;
  for (int i = 0; i < str.len; ++i) {
    ret = ((ret << 5) + ret) + str.str[i];
  }
  return ret;
}

static size_t hash_func(string str)
{
  int ret = 0;
  for (int i = 0; i < str.len; ++i) {
    ret += str.str[i];
  }
  return ret;
}

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
    ASSERT(ind != start);
  }
  return ind;
}

void str_hash_set_set(str_hash_set shs, const string str)
{
  size_t ind = get_avail_ind(shs, str);
  if (ind == -1)
    return;
  shs.entries[ind] = str;
}

int str_hash_set_contains(const str_hash_set shs, const string str)
{
  return get_avail_ind(shs, str) == -1;
}

void str_hash_set_set_test()
{
  string a = cstrtostr("hello");
  string b = cstrtostr("World");
  // TODO

  string entries[10];

  str_hash_set set = {
    .entries = entries,
    .len = 10
  };

  ASSERT(!str_hash_set_contains(set, a));
  str_hash_set_set(set, a);
  ASSERT(str_hash_set_contains(set, a));
}
