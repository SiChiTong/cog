# cog/list.h

**Contents**:
- Structures
- Error Messages
- Functions



## Structures

    struct list_node
    {
        struct list_node *next;
        struct list_node *prev;
        void *value;
    };

    struct list
    {
        int length;
        struct list_node *first;
        struct list_node *last;
    };



## Error Messages

    #define LIST_ENULL "list is NULL!"
    #define LIST_EEMPTY "list is empty!"
    #define LIST_EINNODE "input node is NULL!"



## Functions

    struct list *list_create(void);
    void list_destroy(struct list *list);
    void list_clear(struct list *list);
    void list_clear_destroy(struct list *list);

Creates and frees allocated memory of a struct pointer of `list`. **Note**:
`list_destroy()` does not actually free the chained `struct list_node` value
(ie. `list_node.value`), this is by design because the value is of unknown
type.

To properly clear the list values you can use `list_clear()` to only free the
list node value or `list_clear_destroy()` to free the `list_node.value` **and**
the `list_node` itself.

---

    void list_push(struct list *list, void *value);
    void *list_pop(struct list *list);
    void *list_pop_front(struct list *list);

`list_push()`, `list_pop()` and `list_pop_front()` are fairly explanatory, they
push to the end of the list, pop from the back, and last function pops from the
front.

The pop functions returns the pointer to the popped list node value (ie.
`list_node.value`) and then frees the `list_node` from the `list`.

---

    void *list_shift(struct list *list);
    void list_unshift(struct list *list, void *value);

`list_shift()` and `list_unshift()` are interesting functions.
`list_shift()` is essentially a `list_pop_front()` and returns the
`list_node.value` pointer. `list_unshift()` is the opposite of `list_shift()`
and it accepts a pointer to a new value to be added to the list, on success the
function will return `0`, else `-1` on failure.

---

    void *list_remove(
        struct list *list,
        void *target,
        int (*cmp)(const void *, const void *)
    );
    int list_remove_destroy(
        struct list *list,
        void *value,
        int (*cmp)(const void *, const void *),
        void (*free_func)(void *)
    );

`list_remove()` and `list_remove_destroy()` allows for the removal of a
`list_node` with its value, given that the provided `cmp` function returns `0`.

The difference between the two functions is that `list_remove()` removes the
`list_node` and returns the pointer to the node's value.
`list_remove_destory()` on the other hand instead of returning the pointer to
the `list_node` value, it frees the value using provided `free_func` and
returns a `0` or `-1` to denote success or failure.
