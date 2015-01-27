#include <stdlib.h>

#include "stack.h"


struct stack *stack_create(int limit)
{
    struct stack *s;

    s = calloc(1, sizeof(struct stack));
    s->stack = list_create();
    s->limit = limit;
    s->count = 0;

    return s;
}

void stack_destroy(struct stack *s)
{
    list_destroy(s->stack);
    free(s);
}

int stack_push(struct stack *s, void *data)
{
    list_push(s->stack, data);
    s->count++;
    return 0;
}

void *stack_pop(struct stack *s)
{
    void *data;

    data = list_pop(s->stack);
    s->count--;

    return data;
}

int stack_empty(struct stack *s)
{
    return (s->count == 0) ? 1 : 0;
}

int stack_full(struct stack *s)
{
    if (s->limit != 0 && s->limit == s->count) {
        return 1;
    } else {
        return 0;
    }
}

void *stack_bottom(struct stack *s)
{
    if (s->count != 0) {
        return s->stack->first->value;
    } else {
        return NULL;
    }
}

void *stack_top(struct stack *s)
{
    if (s->count != 0) {
        return s->stack->last->value;
    } else {
        return NULL;
    }
}
