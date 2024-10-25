#pragma once

#include <stddef.h>

#define HASHMAP_INITIAL_CAPACITY 4
#define HASHMAP_GROWTH_FACTOR 1.25

typedef struct pair {
    char *key;
    void *value;
    struct pair *next;
} pair_t;

typedef struct hashmap {
    pair_t **list;
    size_t capacity;
    size_t size;
} hashmap_t;

/**
 * Initialise a hashmap.
 *
 * @param hashmap The address of the hashmap.
 *
 * @returns An error code.
 * @retval 0 if the hashmap was initialised successfully.
 * @retval -1 otherwise.
 */
int hashmap_init(hashmap_t *hashmap);

/**
 * Ensure that the storage capacity of a hashmap is large enough
 * to hold the designated number of items, resizing the encapsulated
 * list if necessary, without modifying the size.
 *
 * @param hashmap The address of the hashmap.
 * @param new_size The required minimum capacity for the hashmap.
 */
void hashmap_ensure_capacity(hashmap_t *hashmap, size_t new_size);

/**
 * Retrieve a value from a hashmap.
 *
 * @param hashmap The address of the hashmap.
 * @param key The key.
 *
 * @returns The value associated with the given `key` if found.
 * @retval NULL if the key is not found.
 */
void *hashmap_get(hashmap_t *hashmap, char *key);

/**
 * Retrieve a hashcode from a hashmap.
 *
 * @param hashmap The address of the hashmap.
 * @param key The key.
 *
 * @returns The hashcode associated with the given `key`.
 */
unsigned int hashcode(hashmap_t *hashmap, char *key);

/**
 * Set a value in a hashmap.
 *
 * @param hashmap The address of the hashmap.
 * @param key The key.
 * @param value The value to store.
 */
void hashmap_set(hashmap_t *hashmap, char *key, void *value);

/**
 * Destroy a hashmap.
 *
 * @attention The hashmap is not fit for further use after this operation.
 *
 * @param hashmap The address of the hashmap.
 */
void hashmap_destroy(hashmap_t *hashmap);
