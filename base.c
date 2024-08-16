#include "base.h"

int strequal(const char* left, const char* right)
{
  if (left == NULL && right == NULL) {
    return 1;
  }

  int i = 0;
  while (1) {
    if (left[i] != right[i])
      return 0;
    if (left[i] == '\0')
      return 1;
    i++;
  }
}

int strcontains(const char* str, const char ch)
{
  int i = 0;
  while (str[i] != '\0') {
    if (ch == str[i])
      return 1;
    i++;
  }
  return 0;
}

#include <stdio.h>
static const char* ignore_chars = " .,;:\"\'-=";

static void load_bfile(BFILE* fp)
{
  ASSERT(fp->ind == BFILE_SIZE);
  size_t read = fread(fp->buffer, 1, BFILE_SIZE, fp->fp);
  ASSERT(read <= BFILE_SIZE);
  if (read != BFILE_SIZE) {
    fp->eof = read;
  }
  fp->ind = 0;
}

BFILE bfopen(const char* filename, const char* mode)
{
  BFILE ret;
  ret.fp = fopen(filename, mode);
  ret.eof = -1;
  load_bfile(&ret);
  return ret;
}

int fpeek(FILE* fp)
{
  int c = fgetc(fp);
  if (c != EOF) {
    ungetc(c, fp);
  }
  return c;
}

int bfgetc(BFILE* fp)
{
  ASSERT(fp->ind <= BFILE_SIZE);
  ASSERT(fp->eof < BFILE_SIZE);

  if (fp->ind == BFILE_SIZE) {
    load_bfile(fp);
  }

  if ((ssize_t)fp->ind == fp->eof)
    return EOF;

  return fp->buffer[fp->ind++];
}

// TODO
int bungetc(int ch, BFILE* fp)
{
  if (fp->ind == 0) {
    fseek(fp->fp, -BFILE_SIZE - 1, SEEK_CUR);
  } else {
    if (ch != fp->buffer[fp->ind - 1])
      return EOF;
    fp->ind--;
  }
  return ch;
}

int bfpeek(BFILE* fp)
{
  int c;
  if (fp->ind == BFILE_SIZE - 1) {
    c = fpeek(fp->fp);
  } else {
    c = fp->buffer[fp->ind + 1];
  }
  return c;
}

int file_exists(const char* filename)
{
  FILE* fp = fopen(filename, "r");
  if (fp == NULL)
    return 0;
  fclose(fp);
  return 1;
}

int read_until(BFILE* fp, const char* delims)
{
  ASSERT(fp != NULL);
  int ch;
  do {
    ch = bfgetc(fp);
  } while (ch != EOF && strcontains(delims, (char)ch));
  return ch;
}

size_t copy_over(BFILE* ifp, FILE* ofp, const size_t bytes)
{
  size_t b = 0;
  char ch;
  while (b < bytes) {
    if ((ch = bfgetc(ifp)) == EOF)
      return b;
    if (fputc(ch, ofp) == EOF)
      return b;
    b++;
  }
  return b;
}

int go_back_one_char(BFILE* fp)
{
  long pos = ftell(fp->fp);
  if (pos == 0) {
    log_warnln("Going backwards, but already at the start");
    return -1;
  }
  fseek(fp->fp, -1, SEEK_CUR);
  if (fp->ind == 0) {
    fp->ind = BFILE_SIZE - 1;
    load_bfile(fp);
  }
  return 0;
}

size_t copy_over_alpha_num(BFILE* ifp, FILE* ofp)
{
  ASSERT(ifp);
  ASSERT(ofp);

  size_t b = 0;
  char ch;

  while (1) {
    if ((ch = bfgetc(ifp)) == EOF)
      return b;

    if (!ISALPHANUMERIC((char)ch)) {
      go_back_one_char(ifp);
      return b;
    }

    if (fputc(ch, ofp) == EOF)
      return b;

    b++;
  }
  return b;
}

size_t noop_over_alpha_num(BFILE* ifp)
{
  ASSERT(ifp);

  size_t b = 0;
  char ch;

  while (1) {
    if ((ch = bfgetc(ifp)) == EOF)
      return b;

    if (!ISALPHANUMERIC((char)ch)) {
      go_back_one_char(ifp);
      return b;
    }

    b++;
  }
  return b;
}

size_t peek_over_alpha(BFILE* fp)
{
  ASSERT(fp);

  size_t b = 0;
  char ch;
  long start = ftell(fp->fp);

  while (1) {
    if ((ch = fgetc(fp)) == EOF)
      break;

    if (!ISALPHANUMERIC((char)ch)) {
      break;
    }

    b++;
  }

  fseek(fp, start, SEEK_SET);

  return b;
}

size_t noop_over_non_alpha_num(BFILE* fp)
{
  ASSERT(fp);

  size_t b = 0;
  char ch;

  while (1) {
    if ((ch = fgetc(fp)) == EOF)
      return b;

    if (ISALPHANUMERIC((char)ch)) {
      go_back_one_char(fp);
      return b;
    }

    b++;
  }
  return b;
}

void print_next_alpha_num(BFILE* fp)
{
  ASSERT(fp);

  char ch;
  long start = ftell(fp);

  while (1) {
    if ((ch = fgetc(fp)) == EOF)
      break;

    if (!ISALPHANUMERIC((char)ch))
      break;

    printf("%c", ch);
  }
  printf("\n");

  fseek(fp, start, SEEK_SET);
}

size_t djb2_hash(const char* str)
{
  size_t ret = 5381;
  int c;
  int i = 0;
  while ((c = str[i++])) {
    ret = ((ret << 5) + ret) + c;
  }
  return ret;
}

size_t djb2_hash_next_word(BFILE* fp, size_t* word_size)
{
  ASSERT(fp);

  size_t b = 0;
  char ch;
  long start = ftell(fp);

  size_t ret = 5381;

  while (1) {
    if ((ch = fgetc(fp)) == EOF)
      break;

    if (!ISALPHANUMERIC((char)ch)) {
      break;
    }

    b++;
    ret = ((ret << 5) + ret) + (int)ch;
  }

  if (word_size)
    *word_size = b;

  fseek(fp, start, SEEK_SET);

  return ret;
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

uint8_t random_uint8(uint8_t low, uint8_t high)
{
  return low + rand() % (high - low + 1);
}

uint16_t random_uint16(uint16_t low, uint16_t high)
{
  return low + rand() % (high - low + 1);
}

uint32_t random_uint32(uint32_t low, uint32_t high)
{
  return low + rand() % (high - low + 1);
}

uint64_t random_uint64(uint64_t low, uint64_t high)
{
  return low + (uint64_t)(rand() % (high - low + 1));
}

float random_float(float low, float high)
{
  return low + ((float)rand() / RAND_MAX) * (high - low);
}

double random_double(double low, double high)
{
  return low + ((double)rand() / RAND_MAX) * (high - low);
}

void random_uint8s(uint8_t* buffer, size_t length, uint8_t low, uint8_t high)
{
  for (size_t i = 0; i < length; ++i) {
    buffer[i] = random_uint8(low, high);
  }
}

void random_uint16s(uint16_t* buffer, size_t length, uint16_t low, uint16_t high)
{
  for (size_t i = 0; i < length; ++i) {
    buffer[i] = random_uint16(low, high);
  }
}

void random_uint32s(uint32_t* buffer, size_t length, uint32_t low, uint32_t high)
{
  for (size_t i = 0; i < length; ++i) {
    buffer[i] = random_uint32(low, high);
  }
}

void random_uint64s(uint64_t* buffer, size_t length, uint64_t low, uint64_t high)
{
  for (size_t i = 0; i < length; ++i) {
    buffer[i] = random_uint64(low, high);
  }
}

void random_floats(float* buffer, size_t length, float low, float high)
{
  for (size_t i = 0; i < length; ++i) {
    buffer[i] = random_float(low, high);
  }
}

void random_doubles(double* buffer, size_t length, double low, double high)
{
  for (size_t i = 0; i < length; ++i) {
    buffer[i] = random_double(low, high);
  }
}

int token_vectorize(
    const char* input_file,
    const char* output_file,
    const char* mode,
    size_t dim)
{
  BFILE ifp = bfopen(input_file, "r");
  BFILE ofp = bfopen(output_file, mode);
  size_t htl = 4096;
  uint8_t* hash_table = malloc(htl);

  fwrite(&dim, sizeof dim, 1, ofp.fp);

  do {

    size_t len;
    size_t hash = djb2_hash_next_word(&ifp, &len);

    if (!BIT_ARR_AT(hash_table, hash % htl)) {
      fwrite(&len, sizeof(len), 1, ofp.fp);
      if (copy_over_alpha_num(&ifp, ofp.fp) == 0)
        break;
      if (noop_over_non_alpha_num(&ifp) == 0)
        break;
      write_random_floats(ofp.fp, dim, 0, 1);
      SET_BIT_ARR_ON(hash_table, hash % htl);
    } else {
      if (noop_over_alpha_num(&ifp) == 0)
        break;
      if (noop_over_non_alpha_num(&ifp) == 0)
        break;
    }
  } while (1);

  fclose(ifp.fp);
  fclose(ofp.fp);
  free(hash_table);

  return 0;
}
