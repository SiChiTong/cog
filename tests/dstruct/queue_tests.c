#include <stdlib.h>
#include <time.h>

#include "munit.h"
#include "utils.h"

#include "dstruct/queue.h"

/* GLOBAL VARIABLES */
static struct queue *q = NULL;
static char *t1 = "test1 data";
static char *t2 = "test2 data";
static char *t3 = "test3 data";

/* PROTOTYPES */
void setup();
void teardown();
int test_queue_create(void);
int test_queue_enqueue_dequeue(void);
int test_queue_destroy(void);
void test_suite(void);


int test_queue_create(void)
{
    q = queue_create(0);

    mu_check(q != NULL);
    mu_check(q->count == 0);
    mu_check(q->limit == 0);

    return 0;
}

int test_queue_enqueue_dequeue(void)
{
    char *val;

    /* enqueue tests */
    queue_enqueue(q, t1);
    mu_check(queue_first(q) == t1);
    mu_check(queue_last(q) == t1);
    mu_check(q->count == 1);

    queue_enqueue(q, t2);
    mu_check(queue_first(q) == t1);
    mu_check(queue_last(q) == t2);
    mu_check(q->count == 2);

    queue_enqueue(q, t3);
    mu_check(queue_first(q) == t1);
    mu_check(queue_last(q) == t3);
    mu_check(q->count == 3);

    /* dequeue tests */
    val = queue_dequeue(q);
    mu_check(val == t1);
    mu_check(queue_first(q) == t2);
    mu_check(queue_last(q) == t3);
    mu_check(q->count == 2);

    val = queue_dequeue(q);
    mu_check(val == t2);
    mu_check(queue_first(q) == t3);
    mu_check(queue_last(q) == t3);
    mu_check(q->count == 1);

    val = queue_dequeue(q);
    mu_check(val == t3);
    mu_check(queue_first(q) == NULL);
    mu_check(queue_last(q) == NULL);
    mu_check(q->count == 0);

    return 0;
}

int test_queue_destroy(void)
{
    queue_destroy(q);
    return 0;
}

void test_suite(void)
{
    mu_add_test(test_queue_create);
    mu_add_test(test_queue_enqueue_dequeue);
    mu_add_test(test_queue_destroy);
}

int main(void)
{
    test_suite();
    mu_report();
    return 0;
}
