#ifndef __STACK_H__
#define __STACK_H__

#include "list.h"

/* STRUCTURES */
struct stack
{
    int limit;
    int count;
    struct list *stack;
};

/* FUNCTIONS */
struct stack *stack_create(int limit);
void stack_destroy(struct stack *s);
int stack_push(struct stack *s, void *data);
void *stack_pop(struct stack *s);
int stack_empty(struct stack *s);
int stack_full(struct stack *s);
void *stack_bottom(struct stack *s);
void *stack_top(struct stack *s);

#endif
