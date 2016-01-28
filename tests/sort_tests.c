#include "munit.h"

#include "utils.h"
#include "sort.h"

/* PROTOTYPES */
int sorted(void **arr, size_t len, int (*cmp)(const void *, const void *));
int test_selection_sort(void);
int test_insertion_sort(void);
int test_partition(void);
void test_suite(void);


static int intcmp_wrapper(const void *val_1, const void *val_2)
{
    return intcmp(*(int *) val_1, *(int *) val_2);
}

static void **setup(size_t len)
{
    size_t i;
    void **arr;

    arr = malloc(sizeof(void *) * len);
    for (i = 0; i < len; i++) {
        arr[i] = malloc_int(randi(0, 1000));
    }

    return arr;
}

static void teardown(void **array, size_t len)
{
    size_t i;

    for (i = 0; i < len; i++) {
        free(array[i]);
    }
    free(array);
}

int sorted(void **arr, size_t len, int (*cmp)(const void *, const void *))
{
    size_t i;

    for (i = 1; i < len - 1; i++) {
        printf("%d\n", *(int *) arr[i]);
        if (cmp(arr[i], arr[i - 1]) < 0) {
            return 0;
        }
    }

    return 1;
}

int test_selection_sort(void)
{
    size_t len;
    void **arr;

    len = 10;
    arr = setup(len);

    selection_sort(arr, len, intcmp_wrapper);
    mu_check(sorted(arr, len, intcmp_wrapper) == 1);

    teardown(arr, len);

    return 0;
}

int test_insertion_sort(void)
{
    size_t len;
    void **arr;

    len = 10;
    arr = setup(len);

    insertion_sort(arr, len, intcmp_wrapper);
    mu_check(sorted(arr, len, intcmp_wrapper) == 1);

    teardown(arr, len);

    return 0;
}

/* int test_partition(void) */
/* { */
/*     int i; */
/*     size_t len; */
/*     void **arr; */
/*  */
/*     len = 10; */
/*     arr = setup(len); */
/*  */
/*     printf("before\n"); */
/*     for (i = 0; i < len; i++) { */
/*         printf("%d\n", *(int *) arr[i]); */
/*     } */
/*  */
/*     partition(arr, 5, 0, len - 1, intcmp_wrapper); */
/*     #<{(| mu_check(sorted(arr, len, intcmp_wrapper) == 1); |)}># */
/*  */
/*     printf("\nafter\n"); */
/*     for (i = 0; i < len; i++) { */
/*         printf("%d\n", *(int *) arr[i]); */
/*     } */
/*  */
/*     teardown(arr, len); */
/*  */
/*     return 0; */
/* } */

void test_suite(void)
{
    mu_add_test(test_selection_sort);
    mu_add_test(test_insertion_sort);
    /* mu_add_test(test_partition); */
}

mu_run_tests(test_suite)
