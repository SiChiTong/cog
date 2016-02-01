#include <string.h>

#include "munit.h"
#include "util.h"
#include "list.h"

/* GLOBAL VARIABLES */
static struct list *list = NULL;

/* PROTOTYPES */
void setup(void);
void teardown(void);
int strcmp_wrapper(const void *v1, const void *v2);
int test_list_create_and_destroy(void);
int test_list_push_pop(void);
int test_list_shift(void);
int test_list_unshift(void);
int test_list_remove(void);
int test_list_remove_destroy(void);
void test_suite(void);


void setup(void)
{
    list = list_create();
}

void teardown(void)
{
    list_clear_destroy(list);
}

int strcmp_wrapper(const void *v1, const void *v2)
{
    return strcmp(v1, v2);
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
    char *t1;
    char *t2;
    char *t3;
    char *val;

    setup();

    t1 = malloc_string("test1 data");
    t2 = malloc_string("test2 data");
    t3 = malloc_string("test3 data");

    /* push tests */
    list_push(list, t1);
    mu_check(strcmp(list->last->value, t1) == 0);

    list_push(list, t2);
    mu_check(strcmp(list->last->value, t2) == 0);

    list_push(list, t3);
    mu_check(strcmp(list->last->value, t3) == 0);
    mu_check(list->length == 3);

    /* pop tests */
    val = list_pop(list);
    mu_check(val == t3);
    mu_check(list->first->value == t1);
    mu_check(list->last->value == t2);
    mu_check(list->length == 2);
    free(val);

    val = list_pop(list);
    mu_check(val == t2);
    mu_check(list->first->value == t1);
    mu_check(list->last->value == t1);
    mu_check(list->length == 1);
    free(val);

    val = list_pop(list);
    mu_check(val == t1);
    mu_check(list->first == NULL);
    mu_check(list->last == NULL);
    mu_check(list->length == 0);
    free(val);

    teardown();

    return 0;
}

int test_list_shift(void)
{
    char *t1;
    char *t2;
    char *val;

    setup();

    t1 = malloc_string("test1 data");
    t2 = malloc_string("test2 data");

    /* push elements */
    list_push(list, t1);
    list_push(list, t2);

    /* test shift */
    val = list_shift(list);
    mu_check(val == t1);
    mu_check(list->length == 1);
    free(val);

    val = list_shift(list);
    mu_check(val == t2);
    mu_check(list->length == 0);
    free(val);

    teardown();

    return 0;
}

int test_list_unshift(void)
{
    char *t1;
    char *t2;
    char *t3;

    setup();

    t1 = malloc_string("test1 data");
    t2 = malloc_string("test2 data");
    t3 = malloc_string("test3 data");

    /* test unshift */
    list_unshift(list, t1);
    mu_check(strcmp(list->first->value, t1) == 0);
    mu_check(strcmp(list->first->value, t1) == 0);
    mu_check(list->length == 1);

    list_unshift(list, t2);
    mu_check(strcmp(list->first->value, t2) == 0);
    mu_check(strcmp(list->first->value, t2) == 0);
    mu_check(list->length == 2);

    list_unshift(list, t3);
    mu_check(strcmp(list->first->value, t3) == 0);
    mu_check(strcmp(list->first->value, t3) == 0);
    mu_check(list->length == 3);

    teardown();

    return 0;
}

int test_list_remove(void)
{
    char *t1;
    char *t2;
    char *t3;
    void *value;

    setup();

    t1 = malloc_string("test1 data");
    t2 = malloc_string("test2 data");
    t3 = malloc_string("test3 data");

    /* push elements */
    list_push(list, t1);
    list_push(list, t2);
    list_push(list, t3);

    /* remove 2nd value */
    value = list_remove(list, t2, strcmp_wrapper);
    free(value);

    /* assert */
    mu_check(list->length == 2);
    mu_check(strcmp(list->first->next->value, t3) == 0);
    mu_check(strcmp(list->first->value, t1) == 0);

    /* remove 2nd value */
    value = list_remove(list, t3, strcmp_wrapper);
    free(value);

    /* assert */
    mu_check(list->length == 1);
    mu_check(list->first->next == NULL);
    mu_check(strcmp(list->first->value, t1) == 0);

    teardown();

    return 0;
}

int test_list_remove_destroy(void)
{
    char *t1;
    char *t2;
    char *t3;
    int result;

    setup();

    t1 = malloc_string("test1 data");
    t2 = malloc_string("test2 data");
    t3 = malloc_string("test3 data");

    /* push elements */
    list_push(list, t1);
    list_push(list, t2);
    list_push(list, t3);

    /* remove 2nd value */
    result = list_remove_destroy(list, t2, strcmp_wrapper, free);

    /* assert */
    mu_check(result == 0);
    mu_check(list->length == 2);
    mu_check(strcmp(list->first->next->value, t3) == 0);
    mu_check(strcmp(list->first->value, t1) == 0);

    /* remove 2nd value */
    result = list_remove_destroy(list, t3, strcmp_wrapper, free);

    /* assert */
    mu_check(result == 0);
    mu_check(list->length == 1);
    mu_check(list->first->next == NULL);
    mu_check(strcmp(list->first->value, t1) == 0);

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
    mu_add_test(test_list_remove_destroy);
}

mu_run_tests(test_suite)
