#ifndef __SEARCH_H__
#define __SEARCH_H__

/* FUNCTIONS */
int sequential_search(
    void *arr,
    size_t el_sz,
    int low,
    int high,
    void *target,
    int(*cmp)(const void *,const void *)
);
int binary_search(
    void *arr,
    size_t el_sz,
    int low,
    int high,
    void *target,
    int(*cmp)(const void *,const void *)
);

#endif
