#include "dstruct/queue.h"


struct queue *queue_create(int limit)
{
    struct queue *q;

    q = calloc(1, sizeof(struct queue));
    q->queue = list_create();
    q->limit = limit;
    q->count = 0;

    return q;
}

void queue_destroy(struct queue *q)
{
    list_destroy(q->queue);
    free(q);
}

int queue_enqueue(struct queue *q, void *data)
{
    list_push(q->queue, data);
    q->count++;
    return 0;
}

void *queue_dequeue(struct queue *q)
{
    void *data;

    data = list_pop_front(q->queue);
    q->count--;

    return data;
}

int queue_empty(struct queue *q)
{
    return (q->count == 0) ? 1 : 0;
}

int queue_full(struct queue *q)
{
    if (q->limit != 0 && q->limit == q->count) {
        return 1;
    } else {
        return 0;
    }
}

void *queue_first(struct queue *q)
{
    if (q->count != 0) {
        return q->queue->first->value;
    } else {
        return NULL;
    }
}

void *queue_last(struct queue *q)
{
    if (q->count != 0) {
        return q->queue->last->value;
    } else {
        return NULL;
    }
}
