#include "base.h"
#include <stdio.h>

#define BFILE_LEN 100

typedef struct {
  FILE* fp;
  char buffer[BFILE_LEN];
  size_t ind;
  ssize_t eof; // -1 if no eof, otherwise ind of eof
} RBFILE;

typedef struct {
  FILE* fp;
  char buffer[BFILE_LEN];
  size_t ind;
} WBFILE;

int rbfseek(RBFILE* fp, long int off, int wnc);

long int rbftell(RBFILE* fp);

RBFILE rbfopen(const char* filename);

int rbfgetc(RBFILE* fp);

int rbungetc(int ch, RBFILE* fp);

int rbfpeek(RBFILE* fp);
