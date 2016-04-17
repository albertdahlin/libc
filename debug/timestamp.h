#pragma once

#include <stdio.h>
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
