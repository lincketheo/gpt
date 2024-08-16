
////////////////////////////////////////////////////
////////// Section: Types
#include <stdint.h>

#define usize size_t

////////////////////////////////////////////////////
////////// Section: Common
#define STMNT(expr) \
  do {              \
    expr;           \
  } while (0)

#define ENABLE_ASSERT 1
#if !defined(AssertBreak)
#define AssertBreak() (*(volatile int*)0 = 0)
#endif
#if ENABLE_ASSERT
#define ASSERT(expr) STMNT(if (!(expr)) { AssertBreak(); })
#else
#define ASSERT(expr)
#endif

#define IN_INC(val, min, max) ((val) >= (min) && (val) <= (max))

#define ISALPHANUMERIC(ch) (IN_INC(ch, 'A', 'Z') || IN_INC(ch, 'a', 'z') || IN_INC(ch, '0', '9'))

#define MAX(a, b) ((a) < (b) ? (b) : (a))

////////////////////////////////////////////////////
////////// Section: Logging
#include <stdio.h>
#define TAG 0
#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define BOLD_BLACK "\033[1;30m"
#define BOLD_RED "\033[1;31m"
#define BOLD_GREEN "\033[1;32m"
#define BOLD_YELLOW "\033[1;33m"
#define BOLD_BLUE "\033[1;34m"
#define BOLD_MAGENTA "\033[1;35m"
#define BOLD_CYAN "\033[1;36m"
#define BOLD_WHITE "\033[1;37m"
#define RESET "\033[0m"

#ifndef NLOGS
#define log_common(fp, color, prefix, fmt, ...) fprintf(fp, BOLD_##color prefix RESET color " [%s(%s:%d)]: " RESET fmt, __FILE__, __func__, __LINE__, ##__VA_ARGS__);
#else
#define log_common(fp, color, prefix, fmt, ...)
#endif

#define log_infoln(fmt, ...) log_common(stdout, WHITE, "INFO", fmt "\n", ##__VA_ARGS__)

#ifdef LDEBUG
#define log_debugln(fmt, ...) log_common(stdout, BLUE, "DEBUG", fmt "\n", ##__VA_ARGS__)
#define log_debugln_expr(expr) STMNT(log_debugln(#expr); expr;)
#else
#define log_debugln(fmt, ...)
#define log_debugln_expr(expr) expr;
#endif

#define log_warnln(fmt, ...) log_common(stderr, YELLOW, "WARN", fmt "\n", ##__VA_ARGS__)
#define log_errorln(fmt, ...) log_common(stderr, RED, "ERROR", fmt "\n", ##__VA_ARGS__);
#define log_errorln_errno(fmt, ...)  STMNT(log_errorln(fmt, ##__VA_ARGS__); errno ? perror(__func__);)

////////////////////////////////////////////////////
////////// Section: Strings
int strequal(const char* left, const char* right);

int strcontains(const char* str, const char ch);

////////////////////////////////////////////////////
////////// Section: Bytes
#define BIT_MASK8_R(n) (1 << (n))
#define BIT_MASK8_L(n) (1 << (7 - n))
#define BIT_AT_L(d, n) ((d & BIT_MASK8_L(n)) >> (7 - n))
#define BIT_AT_R(d, n) ((d & BIT_MASK8_R(n)) >> (n))

#define SET_BIT_ARR_ON(data, bit) data[bit / 8] |= BIT_MASK8_L(bit % 8)
#define SET_BIT_ARR_OFF(data, bit) data[bit / 8] &= ~BIT_MASK8_L(bit % 8)
#define BIT_ARR_AT(data, bit) BIT_AT_L(data[bit / 8], bit % 8)

////////////////////////////////////////////////////
////////// Section: Files

#define BFILE_SIZE 100

typedef struct {
  char buffer[BFILE_SIZE];
  size_t ind;
  ssize_t eof;
  FILE* fp;
} BFILE;

BFILE bfopen(const char* filename, const char* mode);

int fpeek(FILE* fp);

int bfgetc(BFILE* fp);

int bungetc(int ch, BFILE* fp);

int bfpeek(BFILE* fp);

int file_exists(const char* filename);

int read_until(BFILE* fp, const char* delims);

size_t copy_over(BFILE* ifp, FILE* ofp, const size_t bytes);

size_t copy_over_alpha_num(BFILE* ifp, FILE* ofp);

size_t noop_over_alpha_num(BFILE* ifp);

size_t peek_over_alpha(BFILE* fp);

size_t noop_over_non_alpha_num(BFILE* fp);

size_t write_random_floats(FILE* fp, size_t num, float low, float high);

void print_next_alpha_num(BFILE* fp);

////////////////////////////////////////////////////
////////// Section: Hashing

size_t djb2_hash(const char* str);

size_t djb2_hash_next_word(BFILE* fp, size_t* word_size);

////////////////////////////////////////////////////
////////// Section: Numerical
#include <stdlib.h> // rand

////////// Random
uint8_t random_uint8(uint8_t low, uint8_t high);
uint16_t random_uint16(uint16_t low, uint16_t high);
uint32_t random_uint32(uint32_t low, uint32_t high);
uint64_t random_uint64(uint64_t low, uint64_t high);
float random_float(float low, float high);
double random_double(double low, double high);

void random_uint8s(uint8_t* buffer, size_t length, uint8_t low, uint8_t high);
void random_uint16s(uint16_t* buffer, size_t length, uint16_t low, uint16_t high);
void random_uint32s(uint32_t* buffer, size_t length, uint32_t low, uint32_t high);
void random_uint64s(uint64_t* buffer, size_t length, uint64_t low, uint64_t high);
void random_floats(float* buffer, size_t length, float low, float high);
void random_doubles(double* buffer, size_t length, double low, double high);

////////////////////////////////////////////////////
////////// Section: Token Vectorize
int token_vectorize(
    const char* input_file,
    const char* output_file,
    const char* mode,
    size_t dim);

////////////////////////////////////////////////////
////////// Section: Data Structures
/// Singly Linked List
#define LL_PUSH(h, n, v) \
  do {                   \
    (n)->val = (v);      \
    if ((h) == NULL) {   \
      (h) = (n);         \
      (n)->next = NULL;  \
    } else {             \
      (n)->next = (h);   \
      (h) = (n);         \
    }                    \
  } while (0);
