# cog/darray.h

## Structures

    struct darray
    {
        int end;
        int max;

        size_t element_size;
        size_t expand_rate;

        void **contents;
    };


## Constants

    #ifndef DEFAULT_EXPAND_RATE
      #define DEFAULT_EXPAND_RATE 300
    #endif

## Error Message

    #define DARRAY_ENULL "darray is NULL!"
    #define DARRAY_EEL "element is NULL!"
    #define DARRAY_ECMP "comparator is NULL!"
    #define DARRAY_EEMPTY "darray is empty!"
    #define DARRAY_EINDEXOUT "index is out of bounds!"
    #define DARRAY_EELSIZE "element size must be > 0!"
    #define DARRAY_EINITMAX "initial max must be > 0!"
    #define DARRAY_ENEWMAX "new max must be > 0!"
    #define DARRAY_EEXPAND "failed to expand array to new size: %d"


## FUNCTIONS

    struct darray *darray_new(size_t element_size, size_t initial_max);
    void darray_destroy(struct darray *array);

Create and destroys a `struct darray` of `initial_max` elements, each of
`element_size`.

---

    void darray_clear(struct darray *array);
    void darray_clear_destroy(struct darray *array);

`darray_clear()` and `darray_clear_destroy()` functions  both free the `darray`,
with the latter applying the `free()` function to each array element.

---

    int darray_push(struct darray *array, void *el);
    void *darray_pop(struct darray *array);

Allows one to push and pop from `array`:

**Note**: You must use these two with **extreme** caution, if you use these two
functions to push and pop elements to `darray` then you must only use them to
add or remove elements, this is to preserve the consistency of the indices in
`darray`.

---

    int darray_contains(
        struct darray *array,
        void *el,
        int (*cmp)(const void *, const void *)
    );

Checks whether the `struct darray` the target element `el` in question, you
must provide a comparator `cmp` to be able to compare between `el` and elements
in `array`.

---

    struct darray *darray_copy(struct darray *array);

Create copy of `array`.

---

    void *darray_new_element(struct darray *array);

Returns pointer to an malloc-ed memory block for a new element in `array`.

---

    void *darray_first(struct darray *array);
    void *darray_last(struct darray *array);

Returns the pointer to the first and last element of `array`.

---

    void darray_set(struct darray *array, int i, void *el);
    void *darray_get(struct darray *array, int i);

Sets and gets element from `array` at index `i`.

---

    void *darray_update(struct darray* array, int i, void *el);

Update `array` element at index `i` with element `el`.

---

    void *darray_remove(struct darray *array, int i);

Remove `array` element at index `i`.

---

    int darray_contract(struct darray *array);
    int darray_expand(struct darray *array);

Contract and expand `array`.
