#include <stdlib.h>
#include <string.h>

#include "search.h"
#include "util.h"


/* int sequential_search( */
/*     void *arr, */
/*     size_t el_sz, */
/*     int low, */
/*     int high, */
/*     void *target, */
/*     int(*cmp)(const void *,const void *) */
/* ) */
/* { */
/*     int i; */
/*  */
/*     for (i = low; i <= high; i++) { */
/*         if (cmp(arr + (el_sz * i), target) == 0) { */
/*             return 1; */
/*         } */
/*     } */
/*  */
/*     return 0; */
/* } */
/*  */
/* int binary_search( */
/*     void *arr, */
/*     size_t el_sz, */
/*     int low, */
/*     int high, */
/*     void *target, */
/*     int(*cmp)(const void *,const void *) */
/* ) */
/* { */
/*     int index = 0; */
/*     int cmp_res = 0; */
/*  */
/*     while (low <= high) { */
/*         index = (low + high) / 2; */
/*         cmp_res = cmp(target, arr + (el_sz * index)); */
/*  */
/*         if (cmp_res == 0) { */
/*             return 1; */
/*         } else if (cmp_res < 0) { */
/*             high = index - 1; */
/*         } else { */
/*             low = index + 1; */
/*         } */
/*     } */
/*  */
/*     return 0; */
/* } */
