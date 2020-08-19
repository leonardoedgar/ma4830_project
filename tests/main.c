# include "unity.h"
# include "test_int.c"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_int() {
    //test stuff
    test_int_add();
    test_int_multiply();
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_int);
    return UNITY_END();
}