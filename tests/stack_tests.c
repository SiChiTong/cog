#include <stdlib.h>
#include <time.h>

#include "munit.h"
#include "utils.h"

#include "stack.h"

/* GLOBAL VARIABLES */
static struct stack *s = NULL;
static char *t1 = "test1 data";
static char *t2 = "test2 data";
static char *t3 = "test3 data";

/* PROTYTPES */
int test_stack_create(void);
int test_stack_push_pop(void);
int test_stack_destroy(void);
void test_suite(void);


int test_stack_create(void)
{
    s = stack_create(0);

    mu_assert(s != NULL, "Failed to create stack!");
    mu_assert(s->count == 0, "Failed to initialize stack!");
    mu_assert(s->limit == 0, "Failed to initialize stack!");

    return 0;
}

int test_stack_push_pop(void)
{
    char *val;

    /* push tests */
    stack_push(s, t1);
    mu_assert(stack_top(s) == t1, "Wrong top val!");
    mu_assert(stack_bottom(s) == t1, "Wrong bottom val!");
    mu_assert(s->count == 1, "Wrong count on push!");

    stack_push(s, t2);
    mu_assert(stack_top(s) == t2, "Wrong top val!");
    mu_assert(stack_bottom(s) == t1, "Wrong bottom val!");
    mu_assert(s->count == 2, "Wrong count on push!");

    stack_push(s, t3);
    mu_assert(stack_top(s) == t3, "Wrong top val!");
    mu_assert(stack_bottom(s) == t1, "Wrong bottom val!");
    mu_assert(s->count == 3, "Wrong count on push!");

    /* pop tests */
    val = stack_pop(s);
    mu_assert(val == t3, "Wrong value on pop!");
    mu_assert(stack_top(s) == t2, "Wrong top val!");
    mu_assert(stack_bottom(s) == t1, "Wrong next val!");
    mu_assert(s->count == 2, "Wrong count on push!");

    val = stack_pop(s);
    mu_assert(val == t2, "Wrong value on pop!");
    mu_assert(stack_top(s) == t1, "Wrong top val!");
    mu_assert(stack_bottom(s) == t1, "Wrong next val!");
    mu_assert(s->count == 1, "Wrong count on push!");

    val = stack_pop(s);
    mu_assert(val == t1, "Wrong value on pop!");
    mu_assert(stack_top(s) == NULL, "Wrong top!");
    mu_assert(stack_bottom(s) == NULL, "Wrong next val!");
    mu_assert(s->count == 0, "Wrong count after pop!");

    return 0;
}

int test_stack_destroy(void)
{
    stack_push(s, t1);
    stack_push(s, t2);
    stack_push(s, t3);
    stack_destroy(s);
    return 0;
}

void test_suite(void)
{
    mu_add_test(test_stack_create);
    mu_add_test(test_stack_push_pop);
    mu_add_test(test_stack_destroy);
}

int main(void)
{
    test_suite();
    mu_report();
    return 0;
}
