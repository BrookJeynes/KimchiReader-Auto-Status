#include "hashmap.h"

#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hashmap_init(hashmap_t *hashmap) {
    hashmap->capacity = HASHMAP_INITIAL_CAPACITY;
    hashmap->size     = 0;
    hashmap->list     = malloc(sizeof(pair_t *) * hashmap->capacity);

    if (hashmap->list == NULL) {
        fprintf(stderr, "[Error] - Failed to allocate memory for hashmap.\n");
    }

    return 0;
}

void hashmap_ensure_capacity(hashmap_t *hashmap, size_t new_size) {
    if (new_size > hashmap->capacity) {
        hashmap->capacity = fmax(hashmap->capacity * HASHMAP_GROWTH_FACTOR, new_size);
        hashmap->list     = realloc(hashmap->list, sizeof(void *) * hashmap->capacity);
    }
}

unsigned int hashcode(hashmap_t *hashmap, char *key) {
    int code;

    for (code = 0; *key != '\0'; key++) {
        code = *key + 31 * code;
    }

    return code % hashmap->capacity;
}

void *hashmap_get(hashmap_t *hashmap, char *key) {
    pair_t *current = hashmap->list[hashcode(hashmap, key)];

    while (current) {
        if (!strcmp(current->key, key)) {
            return current->value;
        }

        current = current->next;
    }

    return NULL;
}

void hashmap_set(hashmap_t *hashmap, char *key, void *value) {
    unsigned int index = hashcode(hashmap, key);
    pair_t *current    = hashmap->list[index];

    while (current) {
        // if key has been already in hashmap
        if (!strcmp(current->key, key)) {
            current->value = value;
            return;
        }

        current = current->next;
    }

    hashmap_ensure_capacity(hashmap, hashmap->size + 1);

    // key is not in the hashmap
    pair_t *pair = malloc(sizeof(*pair));
    pair->key    = key;
    pair->value  = value;
    pair->next   = hashmap->list[index];

    hashmap->list[index] = pair;
    hashmap->size++;
}

void hashmap_destroy(hashmap_t *hashmap) {
    for (size_t i = 0; i < hashmap->capacity; i++) {
        free(hashmap->list[i]);
    }
    free(hashmap->list);
    hashmap->size     = 0;
    hashmap->capacity = 0;
    hashmap->list     = NULL;
}
