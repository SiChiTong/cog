#include "utils.h"

#include "list.h"


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

    /* pre-check */
    check(list, LIST_ENULL);

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
    /* pre-check */
    check(list, LIST_ENULL);

    return (list->last != NULL ? list_remove(list, list->last) : NULL);
error:
    return NULL;
}

void *list_pop_front(struct list *list)
{
    void *data;
    struct list_node *first_node;
    struct list_node *next_node;

    /* pre-check */
    check(list->first != NULL, LIST_EEMPTY);

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

void *list_shift(struct list *list)
{
    /* pre-check */
    check(list, LIST_ENULL);

    /* shift */
    return (list->first != NULL ? list_remove(list, list->first) : NULL);
error:
    return NULL;
}

void list_unshift(struct list *list, void *value)
{
    struct list_node *node;

    /* pre-check */
    check(list, LIST_ENULL);

    /* unshift */
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

void *list_remove(struct list *list, struct list_node *n)
{
    void *result = NULL;
    struct list_node *before = NULL;
    struct list_node *after = NULL;

    /* pre-check */
    check(list, LIST_ENULL);
    check(list->first, LIST_EEMPTY);
    check(n, LIST_EINNODE);

    /* remove */
    if (n == list->first && n == list->last) {
        list->first = NULL;
        list->last = NULL;

    } else if (n == list->first) {
        list->first = n->next;
        check(
            list->first != NULL,
            "Invalid list, somehow got a first that is NULL!"
        );
        list->first->prev = NULL;

    } else if (n == list->last) {
        list->last = n->prev;
        check(
                list->last != NULL,
                "Invalid list, somehow got a next that is NULL!"
             );
        list->last->next = NULL;

    } else {
        before = n->prev;
        after = n->next;
        after->prev = before;
        before->next = after;

    }

    result = n->value;
    free(n);
    list->length--;
error:
    return result;
}
