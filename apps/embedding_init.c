#include "embedding_init.h"
#include "base.h"
#include "file_utils.h"
#include "logging.h"
#include "str_utils.h"

#include <stdio.h>
#include <stdlib.h>

static void print_help(const char* program_name)
{
  printf("Usage: %s input output dim\n", program_name);
}

int main(int argc, char** argv)
{
  if (argc > 1 && strequal(cstrtostr(argv[1]), cstrtostr("help"))) {
    print_help(argv[0]);
    return 0;
  }

  if (argc != 5) {
    print_help(argv[0]);
    return 1;
  }

  char* input = argv[1];
  char* output = argv[2];
  int dim = atoi(argv[3]);

  if (dim < 1) {
    log_errorln("Invalid dimension. Must be greater than 0");
    return 1;
  }

  if (!file_exists(input)) {
    log_errorln("Input file: %s doesn't exist", input);
    return 1;
  }

  return embedding_init(input, output, dim);
}
