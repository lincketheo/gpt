#include "embedding_init.h"
#include "buffered_file.h"
#include <stdio.h>

int embedding_init(
    const char* input_file,
    const char* output_file,
    const char* mode,
    size_t dim)
{
  RBFILE ifp = rbfopen(input_file);
  FILE* ofp = fopen(output_file, mode);
  size_t htl = 4096;
  fwrite(&dim, sizeof dim, 1, ofp);

  do {
    size_t len;
    size_t hash = djb2_hash_next_word(&ifp, &len); // TODO

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
