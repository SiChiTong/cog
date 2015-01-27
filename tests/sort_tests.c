#include "munit.h"

#include "utils.h"
#include "sort.h"

/* PROTOTYPES */
void **setup(size_t len);
void teardown(void **array, size_t len);
int sorted(void **arr, size_t len, int (*cmp)(const void *, const void *));
int test_selection_sort(void);
int test_insertion_sort(void);
void test_suite(void);


void **setup(size_t len)
{
    size_t i;
    void **arr;

    arr = malloc(sizeof(void *) * len);
    for (i = 0; i < len; i++) {
        arr[i] = malloc_int(randi(0, 1000));
    }

    return arr;
}

void teardown(void **array, size_t len)
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

    selection_sort(arr, len, intcmp);
    mu_check(sorted(arr, len, intcmp) == 1);

    teardown(arr, len);

    return 0;
}

int test_insertion_sort(void)
{
    size_t len;
    void **arr;

    len = 10;
    arr = setup(len);

    insertion_sort(arr, len, intcmp);
    mu_check(sorted(arr, len, intcmp) == 1);

    teardown(arr, len);

    return 0;
}

void test_suite(void)
{
    mu_add_test(test_selection_sort);
    mu_add_test(test_insertion_sort);
}

mu_run_tests(test_suite)
