#include <string.h>

#include "munit.h"
#include "dstruct/list.h"

/* GLOBAL VARIABLES */
static struct list *list = NULL;
static char *test1 = "test1 data";
static char *test2 = "test2 data";
static char *test3 = "test3 data";

/* PROTOTYPES */
int test_list_create(void);
int test_list_push_pop(void);
int test_list_unshift(void);
int test_list_remove(void);
int test_list_shift(void);
int test_list_destroy(void);
void test_suite(void);


int test_list_create(void)
{
    list = list_create();
    mu_check(list != NULL);

    return 0;
}

int test_list_push_pop(void)
{
    char *val = NULL;

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

    return 0;
}

int test_list_unshift(void)
{
    list_unshift(list, test1);
    mu_check(strcmp(list->first->value, test1) == 0);

    list_unshift(list, test2);
    mu_check(strcmp(list->first->value, test2) == 0);

    list_unshift(list, test3);
    mu_check(strcmp(list->first->value, test3) == 0);
    mu_check(list->length == 3);

    return 0;
}

int test_list_remove(void)
{
    // we only need to test the middle remove case since push/shift
    // already tests the other cases
    char *val = NULL;

    val = list_remove(list, list->first->next);
    mu_check(val == test2);
    mu_check(list->length == 2);
    mu_check(strcmp(list->first->value, test3) == 0);
    mu_check(strcmp(list->last->value, test1) == 0);

    return 0;
}

int test_list_shift(void)
{
    mu_check(list->length != 0);

    char *val = list_shift(list);
    mu_check(val == test3);

    val = list_shift(list);
    mu_check(val == test1);
    mu_check(list->length == 0);

    return 0;
}

int test_list_destroy(void)
{
    list_clear_destroy(list);
    return 0;
}

void test_suite(void)
{
    mu_add_test(test_list_create);
    mu_add_test(test_list_push_pop);
    mu_add_test(test_list_unshift);
    mu_add_test(test_list_remove);
    mu_add_test(test_list_shift);
    mu_add_test(test_list_destroy);
}

int main(void)
{
    test_suite();
    mu_report();
    return 0;
}