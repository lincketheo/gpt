#include "base.h"
#include <stdlib.h>

static void print_help(const char* program_name)
{
  printf("Usage: %s input output mode dim\n", program_name);
}

int main(int argc, char** argv)
{
  if (argc > 1 && strequal(argv[1], "help")) {
    print_help(argv[0]);
    return 0;
  }

  if (argc != 5) {
    print_help(argv[0]);
    return 1;
  }

  char* input = argv[1];
  char* output = argv[2];
  char* mode = argv[3];
  int dim = atoi(argv[4]);

  if(dim < 1) {
    log_errorln("Invalid dimension. Must be greater than 0");
    return 1;
  }

  if(!strequal(mode, "a") && !strequal(mode, "w")) {
    log_errorln("Invalid mode: %s. Can be 'a' or 'w'", mode);
    return 1;
  }

  if (!file_exists(input)) {
    log_errorln("Input file: %s doesn't exist", input);
    return 1;
  }

  return token_vectorize(input, output, mode, dim);
}
