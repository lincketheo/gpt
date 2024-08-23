#include "file_utils.h"
#include "random_utils.h"

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
    f = random_f32(low, high);
    fwrite(&f, sizeof f, 1, fp);
  }
  return num;
}

size_t write_len_string(
    FILE* fp,
    char* str,
    size_t buf_len)
{
  unsigned int ret = fwrite(&buf_len, sizeof(buf_len), 1, fp);
  return ret + fwrite(str, buf_len, 1, fp);
}
