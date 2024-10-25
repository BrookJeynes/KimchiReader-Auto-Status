#include "./hashmap/hashmap.h"
#include "./log/log.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef char *String;
const char *STRUCT_WORDCOUNT_FORMAT = "{%i}\n";
const char *STRUCT_WORD_FORMAT_IN = "(%i, %c, %[^,],)\n";
const char *STRUCT_WORD_FORMAT_OUT = "[%i](%i, %c, %s,)\n";
const String FILE_PATH_WORDS = "./words.dat";

// TODO count user input to make space for serialisation

struct Word {
    int count;
    /// Indicates the status of the word.
    /// U = Unknown
    /// S = Seen
    /// K = Known
    char status;
    int len;
    String word;
};

void serialize(String FILE_PATH_WORDS, hashmap_t *words) {
    FILE *file = fopen(FILE_PATH_WORDS, "w");
    if (file == NULL) {
        log_error("Failed to open .dat file.");
        return;
    }

    fprintf(file, STRUCT_WORDCOUNT_FORMAT, words->size);
    for (size_t i = 0; i < words->capacity; i++) {
        pair_t *current = words->list[i];

        while (current) {
            struct Word *word = current->value;
            fprintf(file, STRUCT_WORD_FORMAT_OUT, word->len, word->count, word->status, word->word);
            current = current->next;
        }
    }

    fclose(file);
}

int deserialise(String FILE_PATH_WORDS, hashmap_t *words) {
    FILE *file = fopen(FILE_PATH_WORDS, "r");
    if (file == NULL) {
        log_error("Failed to open .dat file.");
        return 0;
    }

    int word_count = 0;
    fscanf(file, STRUCT_WORDCOUNT_FORMAT, &word_count);

    if (word_count == 0) {
        fclose(file);
        return 0;
    }

    for (int i = 0; i < word_count; i++) {
        struct Word *new_word = malloc(sizeof(struct Word));
        fscanf(file, "[%i]", &new_word->len);
        new_word->word = malloc(sizeof(char) * new_word->len);
        fscanf(file, STRUCT_WORD_FORMAT_IN, &new_word->count, &new_word->status, new_word->word);
        hashmap_set(words, new_word->word, new_word);
    }

    fclose(file);
    return 0;
}

int add(char *argv[], hashmap_t *words, int new_word_count) {
    argv = (argv + 2);  // Set pointer to begin of words.

    if (access(FILE_PATH_WORDS, R_OK | W_OK) != 0) {
        FILE *file = fopen(FILE_PATH_WORDS, "w");
        if (file == NULL) {
            log_error("Failed to create .dat file.");
            return 1;
        }
        fclose(file);
    }

    if (deserialise(FILE_PATH_WORDS, words) != 0) {
        log_error("Failed to deserialize file.");
        return 1;
    }

    for (int i = 0; i < new_word_count; i++) {
        char *word = argv[i];
        struct Word *v = hashmap_get(words, word);
        if (v != NULL) {
            v->count++;
        } else {
            struct Word *new_word = malloc(sizeof(struct Word));
            new_word->count = 1;
            new_word->status = 'U';
            new_word->len = strlen(argv[i]);
            new_word->word = malloc(sizeof(char) * new_word->len);
            strcpy(new_word->word, argv[i]);
            hashmap_set(words, word, new_word);
        }
    }

    serialize(FILE_PATH_WORDS, words);

    return 0;
}

void usage() {
    printf("Usage: ./korean [OPTIONS] <COMMAND>\n");
    printf("Count the amount of times you've seen words.\n\n");
    printf("\
Commands:\n\
add <words>...     add a word(s) to the .dat file. words must be space seperated.\n\
check              ?\n\
\n\
Options:\n\
-h, --help         display this help and exit.\
            \n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        log_error("You must provide at least 1 argument. See -h or --help for usage.");
        return 1;
    }

    hashmap_t words;
    if (hashmap_init(&words) != 0) {
        log_error("Failed to initialize hashmap.");
        return 1;
    }

    if (strcmp(argv[1], "add") == 0) {
        if (argc < 3) {
            log_error("No word(s) provided. Please provide at least 1 word to add.");
            return 1;
        }

        int new_word_count = argc - 2;
        if (add(argv, &words, new_word_count) != 0) {
            log_error("Failed to add word.");
            return 1;
        }
    } else if (strcmp(argv[1], "check") == 0) {

    } else if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        usage();
        return 0;
    }

    // Free all words.
    for (size_t i = 0; i < words.capacity; i++) {
        pair_t *current = words.list[i];

        while (current) {
            struct Word *word = current->value;
            free(word);
            current = current->next;
        }
    }
    hashmap_destroy(&words);
}
