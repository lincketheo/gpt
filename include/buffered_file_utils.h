#include "buffered_file.h"
#include "mem.h"
#include "str_utils.h"

string read_next_alpha_numeric(
    mem_arena* arena,
    RBFILE* ifp);

void noop_next_alpha_numeric(RBFILE* ifp);

string read_next_non_alpha_numeric(
    mem_arena* arena,
    RBFILE* ifp);

void noop_next_non_alpha_numeric(RBFILE* ifp);

int goto_alpha_numeric(RBFILE* fp);
