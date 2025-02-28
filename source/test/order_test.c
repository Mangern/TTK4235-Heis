#include "../order.h"
#include <stdio.h>
#include <stdbool.h>

#include "test.h"

int order_test_simple() {
    TESTASSERT(1 == 1);
    TESTASSERT((1 + 1) == 2);
    TESTASSERT(0);
    return 1;
}

int test_counter;

int main() {
    TEST(order_test_simple);
    return 0;
}
