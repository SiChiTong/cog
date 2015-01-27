#include "munit.h"

#include "hashmap.h"

/* GLOBAL VARIABLES */
static struct hashmap *map = NULL;
static int traverse_called = 0;
static char *test1 = "test data 1";
static char *test2 = "test data 2";
static char *test3 = "xest data 3";
static char *expect1 = "THE VALUE 1";
static char *expect2 = "THE VALUE 2";
static char *expect3 = "THE VALUE 3";

/* PROTOTYPES */
int test_hashmap_create(void);
int test_hashmapget_set(void);
int test_hashmaptraverse(void);
int test_hashmapdelete(void);
int test_hashmap_destroy(void);
void test_suite(void);


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

int test_hashmap_create(void)
{
    map = hashmap_create(NULL, NULL);
    mu_assert(map != NULL, "Failed to create map!");

    return 0;
}

int test_hashmap_destroy(void)
{
    hashmap_destroy(map);
    return 0;
}

int test_hashmapget_set(void)
{
    int rc;
    char *result;

    rc = hashmap_set(map, test1, expect1);
    mu_assert(rc == 0, "Failed to set &test!");
    result = hashmap_get(map, test1);
    mu_assert(strcmp(result, expect1) == 0, "Wrong value for test1!");

    rc = hashmap_set(map, test2, expect2);
    mu_assert(rc == 0, "Failed to set test2");
    result = hashmap_get(map, test2);
    mu_assert(strcmp(result, expect2) == 0, "Wrong value for test2!");

    rc = hashmap_set(map, test3, expect3);
    mu_assert(rc == 0, "Failed to set test3");
    result = hashmap_get(map, test3);
    mu_assert(strcmp(result, expect3) == 0, "Wrong value for test3!");

    return 0;
}

int test_hashmaptraverse(void)
{
    int rc;

    rc = hashmap_traverse(map, traverse_good_cb);
    mu_assert(rc == 0, "Failed to traverse!");
    mu_assert(traverse_called == 3, "Wrong count traverse!");

    traverse_called = 0;
    rc = hashmap_traverse(map, traverse_fail_cb);
    mu_assert(rc == 1, "Failed to traverse!");
    mu_assert(traverse_called == 2, "Wrong count traverse for fail!");

    return 0;
}

int test_hashmapdelete(void)
{
    char *deleted;
    char *result;

    deleted = hashmap_delete(map, test1);
    mu_assert(deleted != NULL, "Got NULL on delete!");
    mu_assert(strcmp(deleted, expect1) == 0, "Should get test1");
    result = hashmap_get(map, test1);
    mu_assert(result == NULL, "Should delete!");

    deleted = hashmap_delete(map, test2);
    mu_assert(deleted != NULL, "Got NULL on delete!");
    mu_assert(strcmp(deleted, expect2) == 0, "Should get test2");
    result = hashmap_get(map, test2);
    mu_assert(result == NULL, "Should delete!");

    deleted = hashmap_delete(map, test3);
    mu_assert(deleted != NULL, "Got NULL on delete!");
    mu_assert(strcmp(deleted, expect3) == 0, "Should get test3");
    result = hashmap_get(map, test3);
    mu_assert(result == NULL, "Should delete!");

    return 0;
}

void test_suite(void)
{
    mu_add_test(test_hashmap_create);
    mu_add_test(test_hashmapget_set);
    mu_add_test(test_hashmaptraverse);
    mu_add_test(test_hashmapdelete);
    mu_add_test(test_hashmap_destroy);
}

int main(void)
{
    test_suite();
    mu_report();
    return 0;
}
