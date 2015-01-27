#include "munit.h"

#include "utils.h"
#include "darray.h"


/* GLOBAL VARIABLES */
static struct darray *array = NULL;
static int *val1 = NULL;
static int *val2 = NULL;
static int *new_val1 = NULL;
static int *new_val2 = NULL;

/* PROTOTYPES */
void setup(void);
void teardown(void);
int test_darray_create_and_destroy(void);
int test_darray_push_pop(void);
int test_darray_new_element(void);
int test_darray_contains(void);
int test_darray_copy(void);
int test_darray_set_and_get(void);
int test_darray_update(void);
int test_darray_remove(void);
int test_darray_expand_and_contract(void);
void test_suite(void);


void setup(void)
{
    array = darray_create(sizeof(int), 100);
}

void teardown(void)
{
    darray_clear_destroy(array);
}

int test_darray_create_and_destroy(void)
{
    array = darray_create(sizeof(int), 100);

    mu_check(array != NULL);
    mu_check(array->contents != NULL);
    mu_check(array->end == 0);
    mu_check(array->element_size == sizeof(int));
    mu_check(array->max == 100);

    darray_destroy(array);

    return 0;
}

int test_darray_push_pop(void)
{
    int i;
    int *val;

    setup();

    /* test push */
    for (i = 0; i < 1000; i++) {
        val = darray_new_element(array);
        *val = i * 333;
        darray_push(array, val);
    }
    mu_check(array->max == 1300);

    /* test pop */
    for (i = 999; i >= 0; i--) {
        val = darray_pop(array);
        mu_check(val != NULL);
        mu_check(*val == i * 333);
        free(val);
    }

    teardown();
    return 0;
}

int test_darray_contains(void)
{
    int *val;
    int res;

    setup();

    /* set element in array */
    val = darray_new_element(array);
    *val = 99;
    darray_set(array, 0, val);

    /* test contains */
    res = darray_contains(array, val, intcmp);
    mu_check(res == 1);

    teardown();
    return 0;
}

int test_darray_copy(void)
{
    int *val;
    int *val_copy;
    struct darray *array_copy;

    setup();

    /* set element in array */
    val = darray_new_element(array);
    *val = 99;
    darray_set(array, 0, val);

    /* test copy */
    array_copy = darray_copy(array);
    val_copy = darray_get(array_copy, 0);
    mu_check(val != val_copy);
    mu_check(intcmp(val, val_copy) == 0);

    teardown();
    darray_clear_destroy(array_copy);

    return 0;
}

int test_darray_new_element(void)
{
    setup();

    /* test new */
    val1 = darray_new_element(array);
    val2 = darray_new_element(array);

    mu_check(val1 != NULL);
    mu_check(val2 != NULL);

    free(val1);
    free(val2);

    teardown();

    return 0;
}

int test_darray_set_and_get(void)
{
    setup();

    /* test set element */
    val1 = darray_new_element(array);
    val2 = darray_new_element(array);
    darray_set(array, 0, val1);
    darray_set(array, 1, val2);

    /* test get element */
    mu_check(darray_get(array, 0) == val1);
    mu_check(darray_get(array, 1) == val2);

    teardown();

    return 0;
}

int test_darray_update(void)
{
    setup();

    /* set element */
    new_val1 = darray_new_element(array);
    new_val2 = darray_new_element(array);
    *new_val1 = 123;
    *new_val2 = 987;

    /* update */
    darray_update(array, 0, new_val1);
    darray_update(array, 1, new_val2);

    /* assert */
    mu_check(darray_get(array, 0) == new_val1);
    mu_check(darray_get(array, 1) == new_val2);

    teardown();

    return 0;
}

int test_darray_remove(void)
{
    int *val_1;
    int *val_2;
    int *result;

    setup();

    /* set elements */
    val_1 = darray_new_element(array);
    val_2 = darray_new_element(array);
    *val_1 = 123;
    *val_2 = 987;
    darray_set(array, 0, val_1);
    darray_set(array, 1, val_2);

    /* remove element at index = 0 */
    result = darray_remove(array, 0);
    mu_check(result != NULL);
    mu_check(*result == *val_1);
    mu_check(darray_get(array, 0) == NULL);
    free(result);

    /* remove element at index = 1 */
    result = darray_remove(array, 1);
    mu_check(result != NULL);
    mu_check(*result == *val_2);
    mu_check(darray_get(array, 1) == NULL);
    free(result);

    teardown();

    return 0;
}

int test_darray_expand_and_contract(void)
{
    size_t old_max;

    setup();

    /* test expand */
    old_max = (unsigned int) array->max;
    darray_expand(array);
    mu_check((unsigned int) array->max == old_max + array->expand_rate);

    /* test contract */
    darray_contract(array);
    mu_check((unsigned int) array->max == array->expand_rate + 1);

    teardown();

    return 0;
}

void test_suite(void)
{
    mu_add_test(test_darray_create_and_destroy);
    mu_add_test(test_darray_push_pop);
    mu_add_test(test_darray_contains);
    mu_add_test(test_darray_copy);
    mu_add_test(test_darray_new_element);
    mu_add_test(test_darray_set_and_get);
    mu_add_test(test_darray_update);
    mu_add_test(test_darray_remove);
    mu_add_test(test_darray_expand_and_contract);
}

mu_run_tests(test_suite)
