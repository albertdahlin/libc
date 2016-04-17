#pragma once
#include <stdio.h>
#include <inttypes.h>

#ifdef NDEBUG
#define DUMP(B, S)
#else
#define DUMP(B, S) dump(B, S, __FILE__, __LINE__, __FUNCTION__)
#endif

static void dump(void *buffer, size_t size, const char *file, int line, const char *func)
{
    FILE *logfile;
    #ifdef DEBUG_LOG_FILENAME
    logfile = fopen(DEBUG_LOG_FILENAME, "a");
    #else
    logfile = stderr;
    #endif
    uint8_t *string = (uint8_t *)buffer;
    uint_fast32_t offset, col;
    uint8_t c;
    uint8_t ascii[18];

    offset = 0;

    fprintf(logfile, "in file %s:%d %s(...) - dump of %zu bytes\n", file, line, func, size);

    while (offset < size) {
        fprintf(logfile, "%04" PRIxFAST32 ": ", offset);

        for (col = 0; col < 16; col++) {
            if (col == 8) {
                fprintf(logfile, " ");
                ascii[col] = ' ';
            }

            if (offset + col < size) {
                c = string[offset + col];
                fprintf(logfile, "%02" PRIx8 " ", c);

                if (c >= 32 && c < 127) {
                    ascii[col >= 8 ? col + 1 : col] = c;
                } else {
                    ascii[col >= 8 ? col + 1 : col] = '.';
                }
            } else {
                fprintf(logfile, "   ");
                ascii[col >= 8 ? col + 1 : col] = '\0';
            }
        }
        ascii[17] = '\0';

        fprintf(logfile, "| %s\n", ascii);
        offset += 16;
    }

    fprintf(logfile, "\n");
    fflush(logfile);

    if (logfile != stderr) {
        fclose(logfile);
    }
}
