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
    void *value;
    struct list_node *last;
    struct list_node *before_last;

    value = NULL;
    before_last = NULL;

    /* pre-check */
    check(list, LIST_ENULL);

    /* get last */
    last = list->last;
    silent_check(last);

    value = last->value;
    before_last = last->prev;
    free(last);

    /* pop */
    if (before_last == NULL && list->length == 1) {
        list->last = NULL;
        list->first = NULL;
    } else {
        list->last = before_last;
    }
    list->length--;

    silent_check(before_last);
    before_last->next = NULL;

    return value;
error:
    return value;
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
    void *value;
    struct list_node *first;
    struct list_node *second;

    /* pre-check */
    check(list, LIST_ENULL);
    check(list, LIST_EEMPTY);

    /* shift */
    first = list->first;
    value = first->value;
    second = list->first->next;

    list->first = second;
    list->length--;
    free(first);

    return value;
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

void *list_remove(
    struct list *list,
    void *value,
    int (*cmp)(const void *, const void *)
)
{
    struct list_node *node;

    node = list->first;
    while (node != NULL) {
        if (cmp(node->value, value) == 0) {
            /* in the case of removing last node in list */
            if (node == list->last) {
                list->last = node->prev;
                list->first->next = NULL;
                list->length--;

                node->prev->next = NULL;
                free(node);

            /* remove others */
            } else {
                node->prev->next = node->next;
                free(node);
                list->length--;

            }

            return value;
        }

        node = node->next;
    }

    return NULL;
}