#include "file_utils.h"
#include "random_utils.h"
#include <stdio.h>

int file_exists(const char* filename)
{
  FILE* fp = fopen(filename, "r");
  if (fp == NULL)
    return 0;
  fclose(fp);
  return 1;
}

int fpeek(FILE* fp)
{
  int c = fgetc(fp);
  if (c != EOF) {
    ungetc(c, fp);
  }
  return c;
}

size_t write_random_floats(FILE* fp, size_t num, float low, float high)
{
  float f;
  for (size_t i = 0; i < num; ++i) {
    f = random_float(low, high);
    fwrite(&f, sizeof f, 1, fp);
  }
  return num;
}

size_t write_string(
    FILE* fp,
    string str)
{
  return fwrite(str.str, str.len, 1, fp);
}

size_t write_len_string(
    FILE* fp,
    string str)
{
  size_t ret = fwrite(&str.len, sizeof(str.len), 1, fp);
  return ret + fwrite(str.str, str.len, 1, fp);
}
