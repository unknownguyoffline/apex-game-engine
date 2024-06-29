#pragma once
#include <stdio.h>

#define LOG(...)                                                                                                       \
    printf("log: ");                                                                                                   \
    printf(__VA_ARGS__);                                                                                               \
    printf("\n")
#define WARN(...)                                                                                                      \
    printf("\x1b[33m");                                                                                                \
    printf("warn: ");                                                                                                  \
    printf(__VA_ARGS__);                                                                                               \
    printf("\x1b[0m\n")
#define ERROR(...)                                                                                                     \
    printf("\x1b[31m");                                                                                                \
    printf("error: ");                                                                                                 \
    printf(__VA_ARGS__);                                                                                               \
    printf("\x1b[0m\n")
#define FATAL(...)                                                                                                     \
    printf("\x1b[41m");                                                                                                \
    printf("fatal: ");                                                                                                 \
    printf(__VA_ARGS__);                                                                                               \
    printf("\x1b[0m\n")

#define ENABLE_TRACE

#ifdef ENABLE_TRACE
#define TRACE(...)                                                                                                     \
    printf("\x1b[34m");                                                                                                \
    printf(__VA_ARGS__);                                                                                               \
    printf("\x1b[0m\n")
#else
#define TRACE(...)
#endif
