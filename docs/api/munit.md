# cog/munit.h
`munit` is a minimalistic unit testing framework for C, less than 100 lines. It
is not meant to be fully featured, but it is meant to be as minimal as
possible. The work is heavily based on John Brewer's minunit. The only real
difference is that `munit` does not block if a tests fails, but John Brewer's
minunit does.

## Macros

    /* GLOBAL VARIABLES */
    static int tests = 0;
    static int passed = 0;
    static int failed = 0;

    /* TEST MACROS */
    #define mu_assert(test, message)
    #define mu_check(test)
    #define mu_add_test(test)
    #define mu_report()
    #define mu_run_tests(TEST_SUITE)


## Example

Have a look at the example code in below, it is fairly trivial and intuitive (I
hope).


    #include <stdio.h>

    #include "cog.h"

    /* TEST VARIABLES (For this test!) */
    int foo = 6;
    int bar = 5;

    int test_foo()
    {
        mu_assert(foo == 7, "Error! foo != 7");
        return 0;
    }

    int test_bar()
    {
        mu_check(bar == 5);
        return 0;
    }

    void test_suite() {
        mu_run_test(test_foo);
        mu_run_test(test_bar);
    }

    mu_report(test_suite)
    // NOTE: mu_report() does not require the trailing smei-colon ";"


The above is simply a test to see if foo and bar is 6 and 5. If not then the
error message for the corresponding assert will be displayed. With `munit` we
provide two assert functions `mu_assert()` and `mu_check()` both are
essentially the same except with `mu_check()` you do not have to specify the
error message in the case of a failed test.

An example output of the above test is as follows:

    2 tests, 2 assertions, 0 failures
