#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdlib.h>

#include "list.h"


/* STRUCTURES */
struct queue
{
    int limit;
    int count;
    struct list *queue;
};

/* CONSTANTS */
#ifndef DEFAULT_QUEUE_LIMIT
  #define DEFAULT_QUEUE_LIMIT 100
#endif


/* FUNCTIONS */
struct queue *queue_create(int limit);
void queue_destroy(struct queue *q);
int queue_enqueue(struct queue *q, void *data);
void *queue_dequeue(struct queue *q);
int queue_count(struct queue *q);
int queue_empty(struct queue *q);
int queue_full(struct queue *q);
void *queue_first(struct queue *q);
void *queue_last(struct queue *q);

#endif
