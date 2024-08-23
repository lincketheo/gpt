#include <stdio.h> // FILE

#define BFILE_LEN 100

typedef struct {
  FILE* fp;
  char buffer[BFILE_LEN];
  unsigned int ind;
  int eof; // -1 if no eof, otherwise ind of eof
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
