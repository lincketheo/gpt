#include "file_utils.h"

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
  for (int i = 0; i < num; ++i) {
    f = random_float(low, high);
    fwrite(&f, sizeof f, 1, fp);
  }
  return num;
}

size_t copy_over(RBFILE* ifp, FILE* ofp, const size_t bytes)
{
  size_t b = 0;
  char ch;
  while (b < bytes) {
    if ((ch = rbfgetc(ifp)) == EOF)
      return b;
    if (fputc(ch, ofp) == EOF)
      return b;
    b++;
  }
  return b;
}

size_t copy_over_alpha_num(RBFILE* ifp, FILE* ofp)
{
  ASSERT(ifp);
  ASSERT(ofp);

  size_t b = 0;
  char ch;

  while (1) {
    if ((ch = rbfgetc(ifp)) == EOF)
      return b;

    if (!ISALPHANUMERIC((char)ch)) {
      rbungetc(ch, ifp);
      return b;
    }

    if (fputc(ch, ofp) == EOF)
      return b;

    b++;
  }
  return b;
}

size_t noop_over_alpha_num(RBFILE* ifp)
{
  ASSERT(ifp);

  size_t b = 0;
  char ch;

  while (1) {
    if ((ch = rbfgetc(ifp)) == EOF)
      return b;

    if (!ISALPHANUMERIC((char)ch)) {
      rbungetc(ch, ifp);
      return b;
    }

    b++;
  }
  return b;
}

size_t peek_over_alpha(RBFILE* fp)
{
  ASSERT(fp);

  size_t b = 0;
  char ch;
  long start = rbftell(fp);

  while (1) {
    if ((ch = rbfgetc(fp)) == EOF)
      break;

    if (!ISALPHANUMERIC((char)ch)) {
      break;
    }

    b++;
  }

  rbfseek(fp, start, SEEK_SET);

  return b;
}

size_t noop_over_non_alpha_num(RBFILE* fp)
{
  ASSERT(fp);

  size_t b = 0;
  char ch;

  while (1) {
    if ((ch = rbfgetc(fp)) == EOF)
      return b;

    if (ISALPHANUMERIC((char)ch)) {
      rbungetc(ch, fp);
      return b;
    }

    b++;
  }
  return b;
}

