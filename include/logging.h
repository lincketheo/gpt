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
