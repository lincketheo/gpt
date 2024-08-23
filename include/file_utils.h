#include <stdio.h> // FILE

int file_exists(const char* filename);

int fpeek(FILE* fp);

size_t write_random_floats(
    FILE* fp,
    size_t num,
    float low,
    float high);

size_t write_len_string(
    FILE* fp,
    char* str,
    size_t buf_len);
