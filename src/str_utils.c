#include "str_utils.h"

#define MAX_STRLEN 100
#define ASSERT_STRING(str) ASSERT(str.len <= MAX_STRLEN)

string cstrtostr(char* cstr)
{
  for (int i = 0; i < MAX_STRLEN; ++i) {
    if (cstr[i] == '\0')
      return (string) {
        .len = i,
        .str = cstr
      };
  }
  ASSERT(0 && "Encountered a string that's larger than MAX_STRLEN. Increase MAX_STRLEN or fix your bug");
  return (string) { 0 };
}

int strequal(string str1, string str2)
{
  ASSERT_STRING(str1);
  ASSERT_STRING(str2);

  if (str1.len != str2.len)
    return 0;
  for (size_t i = 0; i < str1.len; ++i) {
    if (str1.str[i] != str2.str[i])
      return 0;
  }
  return 1;
}
