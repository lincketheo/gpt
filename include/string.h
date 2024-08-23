#pragma once

typedef struct {
  char* str;
  unsigned int len;
} string;

string cstrtostr(char* cstr);

int strequal(string str1, string str2);
