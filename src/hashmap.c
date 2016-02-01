#include <stdint.h>
#include <string.h>

#include "util.h"

#include "list.h"
#include "hashmap.h"


static inline int default_compare(void *a, void *b)
{
    return strcmp(a, b);
}

static uint32_t default_hash(void *a)
{
    size_t len;
    char *key;
    uint32_t i;
    uint32_t hash;

    /* setup */
    len = strlen(a);
    key = a;
    i = 0;
    hash = 0;

    /* Simple Bob Jenkins's hash algorithm */
    for (hash = i = 0; i < len; i++) {
        hash += (uint32_t) key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

struct hashmap *hashmap_create(
    int (*hashmap_cmp)(void *, void *),
    uint32_t (*hashmap_hash)(void *)
)
{
    struct hashmap *map;
    size_t list_sz;

    /* setup */
    list_sz = sizeof(struct darray *);
    map = calloc(1, sizeof(struct hashmap));
    check_mem(map);

    /* create bucket */
    map->buckets = darray_create(list_sz, DEFAULT_NUMBER_OF_BUCKETS);
    map->buckets->end = map->buckets->max; // fake out expanding it
    check_mem(map->buckets);

    hashmap_cmp = (hashmap_cmp == NULL) ? default_compare : hashmap_cmp;
    hashmap_hash = (hashmap_hash == NULL) ? default_hash : hashmap_hash;
    map->compare = hashmap_cmp;
    map->hash = hashmap_hash;

    return map;
error:
    free_mem(map, hashmap_destroy);
    return NULL;
}

static void free_bucket(struct darray **bucket)
{
    int i;

    for (i = 0; i < (*bucket)->end; i++) {
        free(darray_get(*bucket, i));
    }

    darray_destroy(*bucket);
}

static void free_buckets(struct hashmap **map)
{
    int i;
    struct darray *bucket;

    for (i = 0; i < ((*map)->buckets)->end; i++) {
        bucket = darray_get((*map)->buckets, i);

        if (bucket) {
            free_bucket(&bucket);
        }
    }

    darray_destroy((*map)->buckets);
}

void hashmap_destroy(struct hashmap *map)
{
    if (map) {
        if (map->buckets) {
            free_buckets(&map);
        }
        free(map);
    }
}

static inline struct hashmap_node *hashmap_node_create(
    uint32_t  hash,
    void *key,
    void *data
)
{
    struct hashmap_node *node;

    /* setup */
    node = calloc(1, sizeof(struct hashmap_node));
    check_mem(node);

    /* create hashmap node */
    node->key = key;
    node->data = data;
    node->hash = hash;

    return node;
error:
    return NULL;
}

static inline struct darray *hashmap_find_bucket(
    struct hashmap *map,
    void *key,
    int create,
    uint32_t *hash_out
)
{
    int bucket_n;
    uint32_t hash;
    struct darray *bucket;

    /* pre-check */
    hash = map->hash(key);
    bucket_n = hash % DEFAULT_NUMBER_OF_BUCKETS;
    check(bucket_n >= 0, HASHMAP_EBUCKET, bucket_n);
    *hash_out = hash; /* store it for return so caller can use it */

    /* find bucket */
    bucket = darray_get(map->buckets, bucket_n);

    /* coundn't find bucket, create one instead */
    if (!bucket && create) {
        /* new bucket, set it up */
        bucket = darray_create(sizeof(void *), DEFAULT_NUMBER_OF_BUCKETS);
        check_mem(bucket);
        darray_set(map->buckets, bucket_n, bucket);
    }

    return bucket;
error:
    return NULL;
}


int hashmap_set(struct hashmap *map, void *key, void *data)
{
    uint32_t hash;
    struct darray *bucket;
    struct hashmap_node *node;

    /* pre-check */
    bucket = hashmap_find_bucket(map, key, 1, &hash);
    check(bucket, HASHMAP_ECBUCKET);

    /* set hashmap  */
    node = hashmap_node_create(hash, key, data);
    check_mem(node);
    darray_push(bucket, node);

    return 0;
error:
    return -1;
}

static inline int hashmap_get_node(
    struct hashmap *map,
    uint32_t hash,
    struct darray *bucket,
    void *key
)
{
    int i;
    struct hashmap_node *node;

    for (i = 0; i < bucket->end; i++) {
        node = darray_get(bucket, i);

        if (node->hash == hash && map->compare(node->key, key) == 0) {
            return i;
        }
    }

    return -1;
}

void *hashmap_get(struct hashmap *map, void *key)
{
    int i = 0;
    uint32_t hash = 0;
    struct darray *bucket;
    struct hashmap_node *node;

    /* find bucket */
    bucket = hashmap_find_bucket(map, key, 0, &hash);
    silent_check(bucket);

    /* find hashmap node */
    i = hashmap_get_node(map, hash, bucket, key);
    silent_check(i != -1);

    /* get value */
    node = darray_get(bucket, i);
    check(node != NULL, HASHMAP_EGET);

    return node->data;
error:
    return NULL;
}

int hashmap_traverse(
    struct hashmap *map,
    int (*hashmap_traverse_cb)(struct hashmap_node *)
)
{
    int i;
    int j;
    int rc;
    struct darray *bucket;
    struct hashmap_node *node;

    rc = 0;
    for (i = 0; i < map->buckets->end; i++) {
        bucket = darray_get(map->buckets, i);

        if (bucket) {
            for (j = 0; j < bucket->end; j++) {
                node = darray_get(bucket, j);
                rc = hashmap_traverse_cb(node);

                if (rc != 0) {
                    return rc;
                }
            }
        }
    }

    return 0;
}

void *hashmap_delete(struct hashmap *map, void *key)
{
    int i = 0;
    uint32_t hash = 0;
    struct darray *bucket;
    struct hashmap_node *node;
    void *data;
    struct hashmap_node *ending;

    /* find bucket containing hashmap node */
    bucket = hashmap_find_bucket(map, key, 0, &hash);
    silent_check(bucket);

    /* from bucket get hashmap node and free it */
    i = hashmap_get_node(map, hash, bucket, key);
    silent_check(i != -1);

    /* get node */
    node = darray_get(bucket, i);
    data = node->data;
    free(node);

    /* check to see if last element in bucket is a node */
    ending = darray_pop(bucket);
    if (ending != node) {
        /* alright looks like it's not the last one, swap it */
        darray_set(bucket, i, ending);
    }

    return data;
error:
    return NULL;
}
