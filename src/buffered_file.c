#include "buffered_file.h"
#include "file_utils.h"

#define ASSERT_RBFILE(bptr) ASSERT((bptr->eof == -1 || (ssize_t)bptr->ind <= bptr->eof) && (bptr->ind <= BFILE_LEN))
#define ASSERT_WBFILE(bptr) ASSERT(bptr->ind <= BFILE_LEN)

static void rbfile_read_into_buffer(RBFILE* fp)
{
  ASSERT_RBFILE(fp);
  ASSERT(fp->ind == 0);

  size_t read = fread(fp->buffer, 1, BFILE_LEN, fp->fp);

  if (read != BFILE_LEN) {
    fp->eof = read;
  }
}

static void shift_rbfile_left(RBFILE* fp, size_t bytes)
{
  ASSERT_RBFILE(fp);
  ASSERT(bytes < BFILE_LEN - fp->ind);

  long start = ftell(fp->fp);
  fseek(fp->fp, -(BFILE_LEN + bytes), SEEK_CUR);
  size_t ind_before = fp->ind;
  fp->ind = 0;
  rbfile_read_into_buffer(fp);
  long end = ftell(fp->fp);

  // Green path -> end = start - bytes.
  // Edge case - edge left => end > start - bytes
  fp->ind = ind_before + start - end;
}

int rbfseek(RBFILE* fp, long int off, int wnc)
{
  ASSERT_RBFILE(fp);
  int ret = fseek(fp->fp, off, wnc);
  fp->ind = 0;
  rbfile_read_into_buffer(fp);
  return ret;
}

long int rbftell(RBFILE* fp)
{
  ASSERT_RBFILE(fp);
  if (fp->eof > -1) {
    return ftell(fp->fp) - (fp->eof - fp->ind);
  } else {
    return ftell(fp->fp) - (BFILE_LEN - fp->ind);
  }
}

RBFILE rbfopen(const char* filename)
{
  RBFILE ret;
  ret.fp = fopen(filename, "r");
  ret.eof = -1;
  ret.ind = 0;
  rbfile_read_into_buffer(&ret);
  return ret;
}

int rbfgetc(RBFILE* fp)
{
  ASSERT_RBFILE(fp);
  ASSERT(fp->ind <= BFILE_LEN);
  ASSERT(fp->eof < BFILE_LEN);

  if (fp->ind == BFILE_LEN) {
    fp->ind = 0;
    rbfile_read_into_buffer(fp);
  }

  if ((ssize_t)fp->ind == fp->eof)
    return EOF;

  return fp->buffer[fp->ind++];
}

int rbungetc(int ch, RBFILE* fp)
{
  ASSERT_RBFILE(fp);
  if (fp->ind == 0) {
    shift_rbfile_left(fp, BFILE_LEN / 2);
  }

  if (ch != fp->buffer[fp->ind - 1])
    return EOF;
  fp->ind--;
  return ch;
}

int rbfpeek(RBFILE* fp)
{
  ASSERT_RBFILE(fp);
  int c;
  if (fp->ind == BFILE_LEN - 1) {
    c = fpeek(fp->fp);
  } else {
    c = fp->buffer[fp->ind];
  }
  return c;
}
