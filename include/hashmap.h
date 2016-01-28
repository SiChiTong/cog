#ifndef __HASHMAP_H__
#define __HASHMAP_H__

#include <stdint.h>

#include "darray.h"


/* STRUCTURES */
struct hashmap {
    struct darray *buckets;
    int (*compare)(void *, void *);
    uint32_t (*hash)(void *);
};

struct hashmap_node {
    void *key;
    void *data;
    uint32_t hash;
};


/* CONSTANTS */
#ifndef DEFEAULT_NUMBER_OF_BUCKETS
  #define DEFAULT_NUMBER_OF_BUCKETS 100
#endif


/* ERROR MESSAGES */
#define HASHMAP_EBUCKET "invalid bucket found: %d"
#define HASHMAP_ECBUCKET "cannot create bucket!"
#define HASHMAP_EGET "cannot find node from bucket, it should exist!"


/* FUNCTIONS */
struct hashmap *hashmap_create(
    int (*hashmap_compare)(void *, void *),
    uint32_t (*hashmap_hash)(void *)
);
void hashmap_destroy(struct hashmap *map);
int hashmap_set(struct hashmap *map, void *key, void *data);
void *hashmap_get(struct hashmap *map, void *key);
int hashmap_traverse(
    struct hashmap *map,
    int (*hashmap_traverse_cb)(struct hashmap_node *node)
);
void *hashmap_delete(struct hashmap *map, void *key);

#endif
