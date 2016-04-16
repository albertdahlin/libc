#include <stdlib.h>
#include <stdio.h>
#include "debug.h"
#include "dump.h"

void testDebug()
{
    DEBUG("This is a debug message.");
    DEBUG("__FILE__ %s", __FILE__);
    DEBUG("__LINE__ %d", __LINE__);
}

void testDump()
{
    char data[256];
    int i;

    for (i = 0; i < 256; i++) {
        data[i] = i;
    }

    DUMP(data, 256);
}

void testLogError()
{
    LOG_ERR("This is a log error.");
    LOG_ERR("Log error with params. int: %d, string: %s.", 103, "String");

    /**
     * Generate an error by opening a non existing file.
     */
    FILE *file = fopen("a-none-existing-file", "r");
    LOG_ERR("Testing errno. The file pointer address is %p", file);
    errno = 0;
}

void testLogWarning()
{
    LOG_WARN("This is a warning message.");
    LOG_WARN("This is a warning message with a param. %s", "Some param");

    /**
     * Generate an error by opening a non existing file.
     */
    FILE *file = fopen("a-none-existing-file", "r");
    LOG_WARN("Testing errno. The file pointer address is %p", file);
    errno = 0;
}

void testLogInfo()
{
    LOG_INFO("This is an info message.");
    LOG_INFO("This is an info message with a param. %s", "some param");
}

FILE *testCheckGetFile(char *filename)
{
    FILE *file = fopen(filename, "r");

    CHECK(file, "Failed to open file: %s", filename);

    return file;

    error:
    return NULL;
}

int testCheck(char *filename)
{
    FILE *file;

    file = testCheckGetFile(filename);

    CHECK(file, "Could not open file.");

    printf("Successfully opened file: %s\n", filename);

    return 1;

    error:
    return 0;
}

int testSentinelDoSomething(int code)
{
    switch (code) {
        case 1:
            LOG_INFO("Code is %d", code);
            break;

        default:
            SENTINEL("This should not run. Exiting.");
    }

    printf("Something is fine\n");

    return 1;

    error:

    return -1;
}

int testSentinel(int code)
{
    int result;

    result = testSentinelDoSomething(code);
    CHECK(result > 0, "Something went wrong");

    printf("Everything is fine\n");

    return 0;

    error:

    return -1;
}

int testCheckMem(int code)
{
    char *pointer;

    switch (code) {
        case 1:
            pointer = malloc(10);
            break;

        default:
            pointer = NULL;
    }

    CHECK_MEM(pointer);

    printf("Memory successfully allocated\n");
    free(pointer);

    return 0;

    error:

    return -1;
}

int testCheckDebug(int code)
{
    CHECK_DEBUG(code == 1, "Code is not 1");
    printf("Code was 1\n");

    return 0;

    error:

    return -1;
}

int main(int argc, char *argv[])
{
    printf("\n== TEST DEBUG ==\n");
    testDebug();

    printf("\n== TEST DUMP ==\n");
    testDump();

    printf("\n== TEST LOG_ERROR ==\n");
    testLogError();

    printf("\n== TEST LOG_WARN ==\n");
    testLogWarning();

    printf("\n== TEST LOG_INFO ==\n");
    testLogInfo();

    printf("\n== TEST CHECK FAIL ==\n");
    testCheck("none-existing-file");

    printf("\n== TEST CHECK OK ==\n");
    testCheck(__FILE__);

    printf("\n== TEST SENTINEL FAIL ==\n");
    testSentinel(10);

    printf("\n== TEST SENTINEL OK ==\n");
    testSentinel(1);

    printf("\n== TEST CHECK_MEM FAIL ==\n");
    testCheckMem(2);

    printf("\n== TEST CHECK_MEM OK ==\n");
    testCheckMem(1);

    printf("\n== TEST CHECK_DEBUG FAIL ==\n");
    testCheckDebug(2);

    printf("\n== TEST CHECK_DEBUG OK ==\n");
    testCheckDebug(1);

    return 0;
}
