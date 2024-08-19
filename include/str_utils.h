#pragma once 

#include "base.h"
#include <sys/types.h>

typedef struct {
  char* str;
  size_t len;
} string;

string cstrtostr(char* cstr);

int strequal(string str1, string str2);
