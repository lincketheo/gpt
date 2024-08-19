#include "buffered_file.h"

int file_exists(const char* filename);

int fpeek(FILE* fp);

size_t write_random_floats(
    FILE* fp,
    usize num,
    float low,
    float high);

size_t copy_over(
    RBFILE* ifp,
    FILE* ofp,
    const size_t bytes);

size_t copy_over_alpha_num(
    RBFILE* ifp,
    FILE* ofp);

size_t noop_over_alpha_num(RBFILE* ifp);

size_t peek_over_alpha(RBFILE* fp);

size_t noop_over_non_alpha_num(RBFILE* fp);
