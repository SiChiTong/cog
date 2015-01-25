#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>

/* STRUCTURES */
struct list_node {
    struct list_node *next;
    struct list_node *prev;
    void *value;
};

struct list {
    int length;
    struct list_node *first;
    struct list_node *last;
};


/* FUNCTIONS */
struct list *list_create(void);
void list_destroy(struct list *list);
void list_clear(struct list *list);
void list_clear_destroy(struct list *list);
void list_push(struct list *list, void *value);
void *list_pop(struct list *list);
void *list_pop_front(struct list *list);
void *list_shift(struct list *list);
void list_unshift(struct list *list, void *value);
void *list_remove(
    struct list *list,
    struct list_node *node
);

#endif
