#include "buffered_file_utils.h"

string read_next_alpha_numeric(mem_arena* a, RBFILE* ifp)
{
  char ch;
  string ret = {
    .str = mem_arena_head(a),
    .len = 0
  };

  while (1) {
    ch = rbfpeek(ifp);

    if (ch == EOF) {
      if (ret.len == 0) {
        ret.str = NULL;
        return ret;
      }
      return ret;
    }

    if (!ISALPHANUMERIC(ch)){
      return ret;
    }

    mem_arena_push_byte_kill(a, ch);

    ret.len++;
    rbfgetc(ifp);
  }
}

void noop_next_alpha_numeric(RBFILE* ifp)
{
  char ch;

  while (1) {
    ch = rbfpeek(ifp);

    if (ch == EOF)
      return;

    if (!ISALPHANUMERIC(ch))
      return;

    rbfgetc(ifp);
  }
}

string read_next_non_alpha_numeric(mem_arena* a, RBFILE* ifp)
{
  char ch;
  string ret = {
    .str = mem_arena_head(a),
    .len = 0
  };

  while (1) {
    ch = rbfpeek(ifp);

    if (ch == EOF) {
      if (ret.len == 0) {
        ret.str = NULL;
        return ret;
      }
      return ret;
    }

    if (ISALPHANUMERIC(ch))
      return ret;

    mem_arena_push_byte_kill(a, ch);

    ret.len++;
    rbfgetc(ifp);
  }
}

void noop_next_non_alpha_numeric(RBFILE* ifp)
{
  char ch;

  while (1) {
    ch = rbfpeek(ifp);

    if (ch == EOF)
      return;

    if (ISALPHANUMERIC(ch))
      return;

    rbfgetc(ifp);
  }
}

int goto_alpha_numeric(RBFILE* fp)
{
  int c = rbfpeek(fp);
  if (c == EOF)
    return EOF;

  if (!ISALPHANUMERIC(c))
    noop_next_non_alpha_numeric(fp);
  return 0;
}
