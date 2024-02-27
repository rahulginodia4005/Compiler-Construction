#include <stdlib.h>

typedef struct hashmap_element {
    void* key;
    void* value;
    struct hashmap_element* next;
} hashmap_element;

typedef struct {
    hashmap_element** buckets;
    size_t bucket_count;
    size_t (*hash_function)(void*);
    int (*key_compare)(void*, void*);
} hashmap;

hashmap* hashmap_create(size_t bucket_count, size_t (*hash_function)(void*), int (*key_compare)(void*, void*)) {
    hashmap* map = malloc(sizeof(hashmap));
    map->buckets = calloc(bucket_count, sizeof(hashmap_element*));
    map->bucket_count = bucket_count;
    map->hash_function = hash_function;
    map->key_compare = key_compare;
    return map;
}

void hashmap_put(hashmap* map, void* key, void* value) {
    size_t hash = map->hash_function(key) % map->bucket_count;
    hashmap_element* element = malloc(sizeof(hashmap_element));
    element->key = key;
    element->value = value;
    element->next = map->buckets[hash];
    map->buckets[hash] = element;
}

void* hashmap_get(hashmap* map, void* key) {
    size_t hash = map->hash_function(key) % map->bucket_count;
    hashmap_element* element = map->buckets[hash];
    while (element) {
        if (map->key_compare(key, element->key) == 0) {
            return element->value;
        }
        element = element->next;
    }
    return NULL;
}

void hashmap_free(hashmap* map) {
    for (size_t i = 0; i < map->bucket_count; i++) {
        hashmap_element* element = map->buckets[i];
        while (element) {
            hashmap_element* next = element->next;
            free(element);
            element = next;
        }
    }
    free(map->buckets);
    free(map);
}