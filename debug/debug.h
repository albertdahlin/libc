#pragma once

#include <stdio.h>
#include <errno.h>
#include <string.h>

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#ifdef NDEBUG
#define DEBUG(M, ...)
#else
#define DEBUG(M, ...) \
    fprintf( \
        stderr, \
        "[DEBUG] (%s:%d %s) " M "\n", \
        __FILE__, \
        __LINE__, \
        __FUNCTION__, \
        ##__VA_ARGS__ \
    )
#endif

#define LOG_ERR(M, ...) \
    fprintf( \
        stderr, \
        "[ERROR] (%s:%d %s) errno: %s - " M "\n", \
        __FILE__, \
        __LINE__, \
        __FUNCTION__, \
        clean_errno(), \
        ##__VA_ARGS__ \
    )

#define LOG_WARN(M, ...) \
    fprintf( \
        stderr, \
        "[WARN] (%s:%d %s) errno: %s - " M "\n", \
        __FILE__, \
        __LINE__, \
        __FUNCTION__, \
        clean_errno(), \
        ##__VA_ARGS__ \
    )

#define LOG_INFO(M, ...)  \
    fprintf( \
        stderr, \
        "[INFO] (%s:%d %s) " M "\n", \
        __FILE__, \
        __LINE__, \
        __FUNCTION__, \
        ##__VA_ARGS__ \
    )

#define CHECK(A, M, ...) \
    if(!(A)) { \
        LOG_ERR(M, ##__VA_ARGS__); \
        errno=0; \
        goto error; \
    }

#define SENTINEL(M, ...) \
    { \
        LOG_ERR(M, ##__VA_ARGS__); \
        errno=0; \
        goto error; \
    }

#define CHECK_DEBUG(A, M, ...) \
    if(!(A)) { \
        DEBUG(M, ##__VA_ARGS__); \
        errno=0; \
        goto error; \
    } \

#define CHECK_MEM(A) CHECK((A), "Could not allocate memory.")
