#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

#define CHECK_DIMS(x, y) \
    do { \
        if (x != y) { \
            fprintf( \
                stderr, \
                "Error, matrix dimensions incompatible. %s:%d %s() - %d != %d\n", \
                __FILE__, __LINE__, __func__, x, y); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

#endif // COMMON_H
