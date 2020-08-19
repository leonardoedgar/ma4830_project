# include "unity.h"
# include "int_header.h"
void test_int_add() {
    TEST_ASSERT(add_int(3, 5) == 8);
}

void test_int_multiply() {
    TEST_ASSERT(multiply_int(3, 5) == 15);
}