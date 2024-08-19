#include <stdio.h>

////////////////////////////////////////////////////
////////// Section: Logging
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
#define log_commonln(fp, color, prefix, ...)                                                               \
  do {                                                                                                     \
    fprintf(fp, BOLD_##color prefix RESET color " [%s(%s:%d)]: " RESET, __FILE__, __func__, __LINE__); \
    fprintf(fp, __VA_ARGS__);                                                                              \
    fprintf(fp, "\n");                                                                                     \
  } while (0)

#else
#define log_commonln(fp, color, prefix, ...)
#endif

#define log_infoln(...) log_commonln(stdout, WHITE, "INFO", __VA_ARGS__)

#define LDEBUG
#ifdef LDEBUG
#define log_debugln(...) log_commonln(stdout, BLUE, "DEBUG", __VA_ARGS__)
#define log_debugln_expr(expr) \
  do {                         \
    log_debugln(#expr);        \
    expr;                      \
  } while (0)
#else
#define log_debugln(...)
#define log_debugln_expr(expr) expr;
#endif

#define log_warnln(...) log_commonln(stderr, YELLOW, "WARN", __VA_ARGS__)
#define log_errorln(...) log_commonln(stderr, RED, "ERROR", __VA_ARGS__);
#define log_errorln_errno(...) \
  do {                         \
    log_errorln(__VA_ARGS__);  \
    errno ? perror(__func__);  \
  } while (0)
