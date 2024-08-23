#define DefaultAbort() (*(volatile int*)0 = 0)

////////////////////////////////////////////////////
////////// Section: Runtime Abort
/// Different from ASSERT - always runs.
/// ASSERT is removed in release, runtime
/// errors could still happen
#if !defined(RuntimeAbort)
#include "logging.h"
#define RuntimeAbort(...)     \
  do {                        \
    log_errorln(__VA_ARGS__); \
    DefaultAbort();           \
  } while (0)
#endif

#define RUNTIME_CHECK(expr, ...) \
  do {                           \
    if (!(expr)) {               \
      RuntimeAbort(__VA_ARGS__); \
    }                            \
  } while (0)

////////////////////////////////////////////////////
////////// Section: Assert
#define ENABLE_ASSERT 1
#if !defined(AssertAbort)
#define AssertAbort() (*(volatile int*)0 = 0)
#endif
#if ENABLE_ASSERT
#define ASSERT(expr) \
  do {               \
    if (!(expr)) {   \
      AssertAbort(); \
    }                \
  } while (0);
#else
#define ASSERT(expr)
#endif
