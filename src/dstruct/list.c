#include "utils.h"

#include "dstruct/list.h"


struct list *list_create()
{
    struct list *list;

    list = calloc(1, sizeof(struct list));
    list->length = 0;
    list->first = NULL;
    list->last = NULL;

    return list;
}

void list_destroy(struct list *list)
{
    struct list_node *node;
    struct list_node *next_node;

    node = list->first;
    while (node != NULL) {
        next_node = node->next;
        free(node);

        node = next_node;
    }

    free(list);
}

void list_clear(struct list *list)
{
    struct list_node *node;
    struct list_node *next_node;

    node = list->first;
    while (node != NULL) {
        next_node = node->next;
        free(node->value);

        node = next_node;
    }
}


void list_clear_destroy(struct list *list)
{
    struct list_node *node;
    struct list_node *next_node;

    node = list->first;
    while (node != NULL) {
        next_node = node->next;
        free(node->value);
        free(node);

        node = next_node;
    }

    free(list);
}


void list_push(struct list *list, void *value)
{
    struct list_node *node;

    /* initialize node */
    node = calloc( 1, sizeof(struct list_node));
    check_mem(node);
    node->value = value;

    /* push node */
    if (list->last == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->length++;
error:
    return;
}

void *list_pop(struct list *list)
{
    struct list_node *node = list->last;
    return (node != NULL ? list_remove(list, node) : NULL);
}

void *list_pop_front(struct list *list)
{
    void *data;
    struct list_node *first_node;
    struct list_node *next_node;

    /* pre-check */
    check(list->first != NULL, "list is empty!");

    /* pop front */
    first_node = list->first;
    data = first_node->value;
    next_node = first_node->next;

    if (next_node != NULL) {
        list->first = next_node;
    } else {
        list->first = NULL;
    }
    list->length--;

    /* clean up */
    free(first_node);

    return data;
error:
    return NULL;
}

void list_unshift(struct list *list, void *value)
{
    struct list_node *node;

    node = calloc(1, sizeof(struct list_node));
    check_mem(node);

    node->value = value;
    if (list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->length++;

error:
    return;
}

void *list_shift(struct list *l)
{
    struct list_node *node = l->first;
    return (node != NULL ? list_remove(l, node) : NULL);
}

void *list_remove(struct list *l, struct list_node *n)
{
    void *result = NULL;
    struct list_node *before = NULL;
    struct list_node *after = NULL;

    check(l->first && l->last, "list is empty!");
    check(n, "node can't be NULL");

    if (n == l->first && n == l->last) {
        l->first = NULL;
        l->last = NULL;

    } else if (n == l->first) {
        l->first = n->next;
        check(
            l->first != NULL,
            "Invalid list, somehow got a first that is NULL!"
        );
        l->first->prev = NULL;

    } else if (n == l->last) {
        l->last = n->prev;
        check(
                l->last != NULL,
                "Invalid list, somehow got a next that is NULL!"
             );
        l->last->next = NULL;

    } else {
        before = n->prev;
        after = n->next;
        after->prev = before;
        before->next = after;

    }

    result = n->value;
    free(n);
    l->length--;
error:
    return result;
}
