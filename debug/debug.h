#pragma once

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>

static char __timestamp_string[20] = {0};

static inline char *getTimestampString()
{
    time_t tt = time(NULL);
    struct tm *ltime = localtime(&tt);

    snprintf(
        __timestamp_string,
        20,
        "%d-%02d-%02d %02d:%02d:%02d",
        ltime->tm_year + 1900,
        ltime->tm_mon + 1,
        ltime->tm_mday,
        ltime->tm_hour,
        ltime->tm_min,
        ltime->tm_sec
    );

    return __timestamp_string;
}

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#ifdef NDEBUG
#define DEBUG(M, ...)
#else
#define DEBUG(M, ...) \
    fprintf( \
        stderr, \
        "[DEBUG] %s (%s:%d %s) " M "\n", \
        getTimestampString(), \
        __FILE__, \
        __LINE__, \
        __FUNCTION__, \
        ##__VA_ARGS__ \
    )
#endif

#define LOG_ERR(M, ...) \
    fprintf( \
        stderr, \
        "[ERROR] %s (%s:%d %s) errno: %s - " M "\n", \
        getTimestampString(), \
        __FILE__, \
        __LINE__, \
        __FUNCTION__, \
        clean_errno(), \
        ##__VA_ARGS__ \
    )

#define LOG_WARN(M, ...) \
    fprintf( \
        stderr, \
        "[WARN] %s (%s:%d %s) errno: %s - " M "\n", \
        getTimestampString(), \
        __FILE__, \
        __LINE__, \
        __FUNCTION__, \
        clean_errno(), \
        ##__VA_ARGS__ \
    )

#define LOG_INFO(M, ...)  \
    fprintf( \
        stderr, \
        "[INFO] %s (%s:%d %s) " M "\n", \
        getTimestampString(), \
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
