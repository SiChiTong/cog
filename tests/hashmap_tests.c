#include "munit.h"

#include "hashmap.h"


/* PROTOTYPES */
int test_hashmap_new(void);
int test_hashmap_get_set(void);
int test_hashmap_traverse(void);
int test_hashmap_delete(void);
void test_suite(void);

/* GLOBAL VARIABLES */
static int traverse_called;

static int traverse_good_cb(struct hashmap_node *node)
{
    debug("KEY: %s", (char *) node->key);
    traverse_called++;
    return 0;
}


static int traverse_fail_cb(struct hashmap_node *node)
{
    debug("KEY: %s", (char *) node->key);
    traverse_called++;

    if (traverse_called == 2) {
        return 1;
    } else {
        return 0;
    }
}

struct hashmap *setup_test(void)
{
    struct hashmap *map;
    char *test1;
    char *test2;
    char *test3;
    char *expect1;
    char *expect2;
    char *expect3;

    /* setup */
    map = hashmap_new();

    /* key and values */
    test1 = "test data 1";
    test2 = "test data 2";
    test3 = "xest data 3";
    expect1 = "THE VALUE 1";
    expect2 = "THE VALUE 2";
    expect3 = "THE VALUE 3";

    /* set */
    hashmap_set(map, test1, expect1);
    hashmap_set(map, test2, expect2);
    hashmap_set(map, test3, expect3);

    return map;
}

void teardown_test(struct hashmap *map)
{
    hashmap_destroy(map);
}

int test_hashmap_new_destroy(void)
{
    struct hashmap *map;

    map = hashmap_new();
    mu_assert(map != NULL, "Failed to create map!");
    hashmap_destroy(map);

    return 0;
}

int test_hashmap_get_set(void)
{
    int rc;
    char *result;
    char *test1;
    char *test2;
    char *test3;
    char *expect1;
    char *expect2;
    char *expect3;
    struct hashmap *map;

    /* setup */
    map = setup_test();

    test1 = "test data 1";
    test2 = "test data 2";
    test3 = "xest data 3";
    expect1 = "THE VALUE 1";
    expect2 = "THE VALUE 2";
    expect3 = "THE VALUE 3";

    /* set and get test1 */
    rc = hashmap_set(map, test1, expect1);
    mu_assert(rc == 0, "Failed to set &test!");
    result = hashmap_get(map, test1);
    mu_assert(strcmp(result, expect1) == 0, "Wrong value for test1!");

    /* set and get test2 */
    rc = hashmap_set(map, test2, expect2);
    mu_assert(rc == 0, "Failed to set test2");
    result = hashmap_get(map, test2);
    mu_assert(strcmp(result, expect2) == 0, "Wrong value for test2!");

    /* set and get test3 */
    rc = hashmap_set(map, test3, expect3);
    mu_assert(rc == 0, "Failed to set test3");
    result = hashmap_get(map, test3);
    mu_assert(strcmp(result, expect3) == 0, "Wrong value for test3!");

    /* clean up */
    teardown_test(map);

    return 0;
}

int test_hashmap_delete(void)
{
    char *deleted;
    char *result;
    char *test1;
    char *test2;
    char *test3;
    char *expect1;
    char *expect2;
    char *expect3;
    struct hashmap *map;

    /* setup */
    map = setup_test();
    test1 = "test data 1";
    test2 = "test data 2";
    test3 = "xest data 3";
    expect1 = "THE VALUE 1";
    expect2 = "THE VALUE 2";
    expect3 = "THE VALUE 3";

    /* delete test1 */
    deleted = hashmap_delete(map, test1);
    mu_check(deleted != NULL);
    mu_check(strcmp(deleted, expect1) == 0);
    free(deleted);

    result = hashmap_get(map, test1);
    mu_check(result == NULL);

    /* delete test2 */
    deleted = hashmap_delete(map, test2);
    mu_check(deleted != NULL);
    mu_check(strcmp(deleted, expect2) == 0);
    free(deleted);

    result = hashmap_get(map, test2);
    mu_check(result == NULL);

    /* delete test3 */
    deleted = hashmap_delete(map, test3);
    mu_check(deleted != NULL);
    mu_check(strcmp(deleted, expect3) == 0);
    free(deleted);

    result = hashmap_get(map, test3);
    mu_check(result == NULL);

    /* clean up */
    teardown_test(map);

    return 0;
}

int test_hashmap_traverse(void)
{
    int retval;
    struct hashmap *map;

    /* setup */
    map = setup_test();

    /* traverse good cb */
    traverse_called = 0;
    retval = hashmap_traverse(map, traverse_good_cb);
    mu_assert(retval == 0, "Failed to traverse!");
    mu_assert(traverse_called == 3, "Wrong count traverse!");

    /* traverse good bad */
    traverse_called = 0;
    retval = hashmap_traverse(map, traverse_fail_cb);
    mu_assert(retval == 1, "Failed to traverse!");
    mu_assert(traverse_called == 2, "Wrong count traverse for fail!");

    /* clean up */
    teardown_test(map);

    return 0;
}

void test_suite(void)
{
    mu_add_test(test_hashmap_new_destroy);
    mu_add_test(test_hashmap_get_set);
    mu_add_test(test_hashmap_delete);
    mu_add_test(test_hashmap_traverse);
}

int main(void)
{
    test_suite();
    mu_report();
    return 0;
}
