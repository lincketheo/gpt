#if !defined(RuntimeBreak)
#include "logging.h"
#define RuntimeBreak(...)     \
  do {                        \
    log_errorln(__VA_ARGS__); \
    *(volatile int*)0 = 0;    \
  } while (0)
#endif

#define RUNTIME_CHECK(expr, ...) \
  do {                           \
    if (!(expr)) {               \
      RuntimeBreak(__VA_ARGS__); \
    }                            \
  } while (0)
