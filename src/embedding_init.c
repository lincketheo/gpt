#include "embedding_init.h"
#include "buffered_file_utils.h"
#include "file_utils.h"
#include "logging.h"
#include "str_hash_set.h"

#define STR_ARENA_MEMORY 10000000
#define HASH_TABLE_LEN 1000000

int embedding_init(
    const char* input_file,
    const char* output_file,
    size_t dim)
{
  RBFILE ifp = rbfopen(input_file);
  FILE* ofp = fopen(output_file, "w");

  mem_arena arena = mem_arena_init(STR_ARENA_MEMORY);

  // We'll come back to this
  fwrite(&dim, sizeof(dim), 1, ofp);

  goto_alpha_numeric(&ifp);

  str_hash_set strs = {
    .entries = mem_arena_malloc_kill(&arena, HASH_TABLE_LEN),
    .len = HASH_TABLE_LEN
  };
  str_hash_set_init(strs);

  while (1) {
    string word = read_next_alpha_numeric(&arena, &ifp);
    if (word.str == NULL)
      break;

    if (!str_hash_set_contains(strs, word)) {
      write_len_string(ofp, word);
      write_random_floats(ofp, dim, 0, 1);
      str_hash_set_set(strs, word);
    }

    noop_next_non_alpha_numeric(&ifp);
  }

  mem_arena_free(&arena);

  return 0;
}
