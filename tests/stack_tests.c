#include "munit.h"
#include "stack.h"
#include "util.h"


/* TESTS */
int test_stack_new_and_destroy(void);
int test_stack_push(void);
int test_stack_pop(void);
void test_suite(void);


int test_stack_new_and_destroy(void)
{
    struct stack *s = stack_new();

    mu_check(s->size == 0);
    mu_check(s->root == NULL);
    mu_check(s->end == NULL);

    stack_destroy(s, free);
    return 0;
}

int test_stack_push(void)
{
    struct stack *s = stack_new();
    float *f1 = malloc_float(2.0);
    float *f2 = malloc_float(4.0);
    float *f3 = malloc_float(8.0);

    /* push float 1 */
    stack_push(s, f1);
    mu_check(fltcmp(*(float *) s->end->value, *(float *) f1) == 0);
    mu_check(s->size == 1);
    mu_check(s->root->value == f1);
    mu_check(s->end->prev == NULL);

    /* push float 2 */
    stack_push(s, f2);
    mu_check(fltcmp(*(float *) s->end->value, *(float *) f2) == 0);
    mu_check(s->size == 2);
    mu_check(s->root->value == f1);
    mu_check(s->end->prev->value == f1);
    mu_check(fltcmp(*(float *) s->end->prev->value, *(float *) f1) == 0);

    /* push float 3 */
    stack_push(s, f3);
    mu_check(fltcmp(*(float *) s->end->value, *(float *) f3) == 0);
    mu_check(s->size == 3);
    mu_check(s->root->value == f1);
    mu_check(s->end->prev->value == f2);
    mu_check(fltcmp(*(float *) s->end->prev->value, *(float *) f2) == 0);

    stack_destroy(s, free);
    return 0;
}

int test_stack_pop(void)
{
    struct stack *s = stack_new();
    float *f1 = malloc_float(2.0);
    float *f2 = malloc_float(4.0);
    float *f3 = malloc_float(8.0);
    float *flt_ptr;

    /* push float 1 */
    stack_push(s, f1);
    mu_check(fltcmp(*(float *) s->end->value, *(float *) f1) == 0);
    mu_check(s->size == 1);
    mu_check(s->root->value == f1);
    mu_check(s->end->prev == NULL);

    /* push float 2 */
    stack_push(s, f2);
    mu_check(fltcmp(*(float *) s->end->value, *(float *) f2) == 0);
    mu_check(s->size == 2);
    mu_check(s->root->value == f1);
    mu_check(s->end->prev->value == f1);
    mu_check(fltcmp(*(float *) s->end->prev->value, *(float *) f1) == 0);

    /* push float 3 */
    stack_push(s, f3);
    mu_check(fltcmp(*(float *) s->end->value, *(float *) f3) == 0);
    mu_check(s->size == 3);
    mu_check(s->root->value == f1);
    mu_check(s->end->prev->value == f2);
    mu_check(fltcmp(*(float *) s->end->prev->value, *(float *) f2) == 0);

    /* pop float 3 */
    flt_ptr = stack_pop(s);
    mu_check(fltcmp(*(float *) flt_ptr, *(float *) f3) == 0);
    mu_check(s->size == 2);
    mu_check(s->root->value == f1);
    mu_check(fltcmp(*(float *) s->root->value, *(float *) f1) == 0);
    free(flt_ptr);

    /* pop float 2 */
    flt_ptr = stack_pop(s);
    mu_check(fltcmp(*(float *) flt_ptr, *(float *) f2) == 0);
    mu_check(s->size == 1);
    mu_check(s->root->value == f1);
    mu_check(fltcmp(*(float *) s->root->value, *(float *) f1) == 0);
    free(flt_ptr);

    /* pop float 1 */
    flt_ptr = stack_pop(s);
    mu_check(fltcmp(*(float *) flt_ptr, *(float *) f1) == 0);
    mu_check(s->size == 0);
    mu_check(s->root == NULL);
    mu_check(s->end == NULL);
    free(flt_ptr);

    stack_destroy(s, free);
    return 0;
}

void test_suite(void)
{
    mu_add_test(test_stack_new_and_destroy);
    mu_add_test(test_stack_push);
    mu_add_test(test_stack_pop);
}

mu_run_tests(test_suite)
