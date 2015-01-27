#include <string.h>

#include "munit.h"
#include "list.h"

/* GLOBAL VARIABLES */
static struct list *list = NULL;
static char *test1 = "test1 data";
static char *test2 = "test2 data";
static char *test3 = "test3 data";

/* PROTOTYPES */
void setup(void);
void teardown(void);
int test_list_create_and_destroy(void);
int test_list_push_pop(void);
int test_list_shift(void);
int test_list_unshift(void);
int test_list_remove(void);
void test_suite(void);


void setup(void)
{
    list = list_create();
}

void teardown(void)
{
    list_clear_destroy(list);
}

int test_list_create_and_destroy(void)
{
    /* create */
    list = list_create();
    mu_check(list != NULL);

    /* clear destroy */
    list_clear_destroy(list);

    return 0;
}

int test_list_push_pop(void)
{
    char *val = NULL;

    setup();

    /* push tests */
    list_push(list, test1);
    mu_check(strcmp(list->last->value, test1) == 0);

    list_push(list, test2);
    mu_check(strcmp(list->last->value, test2) == 0);

    list_push(list, test3);
    mu_check(strcmp(list->last->value, test3) == 0);
    mu_check(list->length == 3);

    /* pop tests */
    val = list_pop(list);
    mu_check(val == test3);

    val = list_pop(list);
    mu_check(val == test2);

    val = list_pop(list);
    mu_check(val == test1);
    mu_check(list->length == 0);

    teardown();

    return 0;
}

int test_list_shift(void)
{
    char *val;

    setup();

    /* push elements */
    list_push(list, test1);
    list_push(list, test2);
    list_push(list, test3);

    /* test shift */
    val = list_shift(list);
    mu_check(val == test1);
    mu_check(list->length == 2);

    val = list_shift(list);
    mu_check(val == test2);
    mu_check(list->length == 1);

    teardown();

    return 0;
}

int test_list_unshift(void)
{
    setup();

    /* test unshift */
    list_unshift(list, test1);
    mu_check(strcmp(list->first->value, test1) == 0);
    mu_check(list->length == 1);

    list_unshift(list, test2);
    mu_check(strcmp(list->first->value, test2) == 0);
    mu_check(list->length == 2);

    list_unshift(list, test3);
    mu_check(strcmp(list->first->value, test3) == 0);
    mu_check(list->length == 3);

    teardown();

    return 0;
}

int test_list_remove(void)
{
    char *val;

    setup();

    /* push elements */
    list_push(list, test1);
    list_push(list, test2);
    list_push(list, test3);

    /* test remove */
    val = list_remove(list, list->first->next);
    mu_check(val == test2);
    mu_check(list->length == 2);
    mu_check(strcmp(list->first->value, test1) == 0);
    mu_check(strcmp(list->last->value, test3) == 0);

    teardown();

    return 0;
}


void test_suite(void)
{
    mu_add_test(test_list_create_and_destroy);
    mu_add_test(test_list_push_pop);
    mu_add_test(test_list_shift);
    mu_add_test(test_list_unshift);
    mu_add_test(test_list_remove);
}

mu_run_tests(test_suite)
