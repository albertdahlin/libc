#ifndef __dump_h__
#define __dump_h__
#include <stdio.h>

#ifdef NDEBUG
#define DUMP(B, S)
#else
#define DUMP(B, S) dump(B, S, __FILE__, __LINE__, __FUNCTION__)
#endif

static void dump(void *buffer, int size, const char *file, int line, const char *func)
{
    FILE *logfile;
#ifdef DEBUG_LOG_FILENAME
    logfile = fopen(DEBUG_LOG_FILENAME, "a");
#else
    logfile = stderr;
#endif
    char *string = (char *)buffer;
    int offset, col;
    char c;
    char ascii[18];

    offset = 0;

    fprintf(logfile, "in file %s:%d %s(...) - dump of %d bytes\n", file, line, func, size);

    while (offset < size) {
        fprintf(logfile, "%04x: ", offset);

        for (col = 0; col < 16; col++) {
            if (col == 8) {
                fprintf(logfile, " ");
                ascii[col] = ' ';
            }

            if (offset + col < size) {
                c = (unsigned char)string[offset + col];
                fprintf(logfile, "%02x ", c & 0xff);

                if (c > 32 && c < 128) {
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
#endif
