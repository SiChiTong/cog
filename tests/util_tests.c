#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef MU_PRINT
  #define MU_PRINT 1
#endif

#include "munit.h"
#include "util.h"


/* TESTS */
int test_intcmp(void);
int test_fltcmp(void);
int test_epsilon_float_cmp(void);
int test_trim_char(void);
int test_trim(void);
int test_split(void);
int test_copy_value(void);
int test_strex(void);
int test_randi(void);
int test_fsize(void);
int test_fstring(void);
int test_fexists(void);
int test_fext(void);
int test_path_join(void);
void test_suite(void);


int test_intcmp()
{
    int val_1;
    int val_2;

    /* setup */
    val_1 = 1;
    val_2 = 1;

    /* ASCENDING TESTS */
    /* when val_1 and val_2 are equal */
    int result = intcmp_asc(val_1, val_2);
    mu_assert(result == 0, "Result should be 0!");

    /* when val_2 is bigger than val_1 */
    val_2 = 10;
    result = intcmp_asc(val_1, val_2);
    mu_assert(result == -1, "Result should be -1!");

    /* when val_1 is bigger than val_2 */
    val_2 = -1;
    result = intcmp_asc(val_1, val_2);
    mu_assert(result == 1, "Result should be 1!");

    /* resetting values */
    val_1 = 1;
    val_2 = 1;

    /* DESCENDING TESTS */
    /* when val_1 and val_2 are equal */
    result = intcmp_desc(val_1, val_2);
    mu_assert(result == 0, "Result should be 0!");

    /* when val_2 is bigger than val_1 */
    val_2 = 10;
    result = intcmp_desc(val_1, val_2);
    mu_assert(result == 1, "Result should be 1!");

    /* when val_1 is bigger than val_2 */
    val_2 = -1;
    result = intcmp_desc(val_1, val_2);
    mu_assert(result == -1, "Result should be -1!");

    return 0;
}

int test_fltcmp()
{
    float val_1;
    float val_2;

    /* setup */
    val_1 = 1.0f;
    val_2 = 1.0f;

    /* ASCENDING TESTS */
    /* when val_1 and val_2 are equal */
    int result = fltcmp_asc(val_1, val_2);
    mu_assert(result == 0, "Result should be 0!");

    /* when val_2 is bigger than val_1 */
    val_1 = 0.001f;
    val_2 = 0.01f;
    result = fltcmp_asc(val_1, val_2);
    mu_assert(result == -1, "Result should be -1!");

    /* when val_1 is bigger than val_2 */
    val_1 = 0.01f;
    val_2 = 0.001f;
    result = fltcmp_asc(val_1, val_2);
    mu_assert(result == 1, "Result should be 1!");


    /* resetting values */
    val_1 = 1.0f;
    val_2 = 1.0f;


    /* DESCENDING TESTS */
    result = fltcmp_desc(val_1, val_2);
    mu_assert(result == 0, "Result should be 0!");

    /* when val_2 is bigger than val_1 */
    val_1 = 0.001f;
    val_2 = 0.01f;
    result = fltcmp_desc(val_1, val_2);
    mu_assert(result == 1, "Result should be 1!");

    /* when val_1 is bigger than val_2 */
    val_1 = 0.01f;
    val_2 = 0.001f;
    result = fltcmp_desc(val_1, val_2);
    mu_assert(result == -1, "Result should be -1!");

    return 0;
}

int test_trim_char(void)
{
    mu_check(trim_char('\n') == 1);
    mu_check(trim_char('\t') == 1);
    mu_check(trim_char('\r') == 1);
    mu_check(trim_char(' ') == 1);
    mu_check(trim_char('A') == 0);

    return 0;
}

int test_trim(void)
{
    char *result;
    const char *test_1 = "\nHello World\n ";
    const char *test_2 = "\n\tWorld\n \t";

    result = trim(test_1);
    mu_check(strcmp(result, "Hello World") == 0);
    free(result);

    result = trim(test_2);
    mu_check(strcmp(result, "World") == 0);
    free(result);

    return 0;
}

int test_split(void)
{
    char **result;
    int size;
    const char *test_1 = "\nHello World\n ";

    result = split(test_1, " ", &size);
    mu_check(strcmp(result[0], "Hello") == 0);
    mu_check(strcmp(result[1], "World") == 0);
    mu_check(size == 2);

    free(result[0]);
    free(result[1]);
    free(result);

    return 0;
}

int test_copy_value(void)
{
    int *int_ptr;
    float *float_ptr;
    double *double_ptr;
    char *str_ptr;

    int int_value = 0;
    float float_value = 10.0;
    double doule_value = 100.0;
    const char *str_value = "test";

    int_ptr = copy_value(INTEGER, &int_value);
    mu_check(intcmp(*int_ptr, int_value) == 0);

    float_ptr = copy_value(FLOAT, &float_value);
    mu_check(fltcmp(*float_ptr, float_value) == 0);

    double_ptr = copy_value(DOUBLE, &doule_value);
    mu_check(fltcmp(*double_ptr, doule_value) == 0);

    str_ptr = copy_value(STRING, (void *) str_value);
    mu_check(strcmp(str_ptr, str_value) == 0);

    /* clean up */
    free(int_ptr);
    free(float_ptr);
    free(double_ptr);
    free(str_ptr);
    return 0;
}

/* int test_strex(void) */
/* { */
/*     char s[100]; */
/*     char *retval; */
/*  */
/*     s = "abcd {efgh} ijkl"; */
/*     retval = strex(s, '{', '}'); */
/*     mu_check(strcmp(retval, "efgh"); */
/*  */
/*     return 0; */
/* } */

int test_randi(void)
{
    int i;
    int retval;
    int counter_1 = 0;
    int counter_2 = 0;
    int counter_3 = 0;

    for (i = 0; i < 10000; i++) {
        retval = randi(0, 2);

        if (retval == 0) {
            counter_1++;
        } else if (retval == 1) {
            counter_2++;
        } else if (retval == 2) {
            counter_3++;
        }
    }

    mu_print("%d, %d, %d\n", counter_1, counter_2, counter_3);

    return 0;
}

int test_fsize(void)
{
    off_t file_size;

    file_size = fsize("./tests/data/test_data.dat");
    mu_print("file_size: %d\n", (int) file_size);
    mu_check((int) file_size > 0);

    return 0;
}

int test_fstring(void)
{
    char *string;

    string = fstring("./tests/data/test_data.dat");
    mu_print("file string: %s\n", string);
    mu_check(string != NULL);
    free(string);

    return 0;
}

int test_fexists(void)
{
    int res;

    res = fexists("README.md");
    mu_check(res == 1);

    res = fexists("./README.md");
    mu_check(res == 1);

    res = fexists("./README.m");
    mu_check(res == 0);

    return 0;
}

int test_fext(void)
{
    char *ext;

    ext = fext("somefile.beforeext.ext");
    mu_check(strcmp(ext, "ext") == 0);
    free(ext);

    return 0;
}

int test_path_join(void)
{
    char *path;
    char *expect;

    /* test join */
    path = path_join(2, "Hello", "World");
    expect = malloc_string("Hello/World");
    mu_print("%s\n", path);
    mu_check(strcmp(expect, path) == 0);
    free(path);
    free(expect);

    /* test join with slash already */
    path = path_join(2, "Hello/", "World");
    expect = malloc_string("Hello/World");
    mu_print("%s\n", path);
    mu_check(strcmp(expect, path) == 0);
    free(path);
    free(expect);

    path = path_join(2, "Hello", "/World");
    expect = malloc_string("Hello/World");
    mu_print("%s\n", path);
    mu_check(strcmp(expect, path) == 0);
    free(path);
    free(expect);

    path = path_join(2, "Hello/", "/World");
    expect = malloc_string("Hello/World");
    mu_print("%s\n", path);
    mu_check(strcmp(expect, path) == 0);
    free(path);
    free(expect);

    return 0;
}


void test_suite(void)
{
    srand((unsigned int) time(NULL));
    mu_add_test(test_intcmp);
    mu_add_test(test_fltcmp);

    mu_add_test(test_trim_char);
    mu_add_test(test_trim);
    mu_add_test(test_split);
    mu_add_test(test_copy_value);

    mu_add_test(test_randi);

    mu_add_test(test_fsize);
    mu_add_test(test_fstring);
    mu_add_test(test_fexists);
    mu_add_test(test_fext);

    mu_add_test(test_path_join);
}

mu_run_tests(test_suite)
