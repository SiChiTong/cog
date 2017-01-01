# cog/hashmap.h


## Structures

    struct hashmap
    {
        struct darray *buckets;
        int (*compare)(void *, void *);
        uint32_t (*hash)(void *);
    };

    struct hashmap_node
    {
        void *key;
        void *data;
        uint32_t hash;
    };


## Constants

    #ifndef DEFEAULT_NUMBER_OF_BUCKETS
      #define DEFAULT_NUMBER_OF_BUCKETS 100
    #endif


## Functions

    struct hashmap *hashmap_create(
        int (*hashmap_compare)(void *, void *),
        uint32_t (*hashmap_hash)(void *)
    );
    void hashmap_destroy(struct hashmap *map);

Create and destroy `struct hashmap`. When you create a hashmap, one must
specify the hashing function `hashmap_hash` and comparator `hashmap_compare`.

---

    int hashmap_set(struct hashmap *map, void *key, void *data);
    void *hashmap_get(struct hashmap *map, void *key);

Sets and gets `struct hashmap` with `key` and `data`.

---

    int hashmap_traverse(
        struct hashmap *map,
        int (*hashmap_traverse_cb)(struct hashmap_node *node)
    );

Traverse `struct hashmap`.  You can supply a traverse callback function
`hashmap_traverse_cb`. The callback function must return `0` to continue.

---

    void *hashmap_delete(struct hashmap *map, void *key);

Delete hashmap key-value pair in `map` with `key`.
