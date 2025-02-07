#ifndef TEST_H
#define TEST_H

#include <stdio.h>

extern int test_counter;

#define STRING(s) #s

#define TESTASSERT(expr) { if (!(expr)) return __LINE__; }

#define TEST(f) do {                                        \
    int ret = f();                                          \
    printf("Test %d: %s\n\t", ++test_counter, STRING(f));   \
    if (ret == 0) {                                         \
        printf("\x1b[1;32mpass\x1b[0m\n");                  \
    } else {                                                \
        printf("\x1b[1;31mfail\x1b[0m on line %d\n", ret);  \
    }                                                       \
} while(0);                                       

#endif
