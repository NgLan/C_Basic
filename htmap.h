#ifndef HTMAP_H
#define HTMAP_H

#define KEY const char *
#define VALUE_T int

// Note: Hien tai thu vien chi dung cho key : const char * va value : int
// Neu dung hash map thi phai sua lai ham compare trong bst.h

#include "bst.h"
#include <time.h>

struct htmap {
    struct tree **cols;
    int size;
    int cap;
};

struct htmap *hashmap(int cap) {
    struct htmap *map = (struct htmap *)malloc(sizeof(struct htmap));
    map->size = 0;
    map->cap = cap;
    map->cols = (struct tree **)calloc(map->cap, sizeof(struct tree *));
}

// Ham bam
unsigned int hash_s(KEY s) {
    KEY p;
    unsigned int h = 5381;
    for (p = s; *p != '\0'; p++) {
        h = (h << 5) + h + *p;
    }
    return h;
}

// Chuyen ma bam thanh index
unsigned htkey2idx(struct htmap *map, KEY key) {
    unsigned hash_code = hash_s(key);
    unsigned idx = hash_code % map->cap;
    return idx;
}

struct tnode *htput(struct htmap *map, KEY key, VALUE_T value) {
    /* Đẩy key và value vào cây ở vị trí idx */
    unsigned idx = htkey2idx(map, key);
    if (map->cols[idx] == NULL) {
        map->cols[idx] = tree();
    }
    struct tnode *n = tput(map->cols[idx], key, value);
    return n;
}

struct tnode *htsearch(struct htmap *map, KEY key) {
    unsigned idx = htkey2idx(map, key);
    if (map->cols[idx] == NULL) {
        return NULL;
    }
    return tsearch(map->cols[idx], key);
}

int htrem(struct htmap *map, KEY key) {
    unsigned idx = htkey2idx(map, key);
    if (map->cols[idx] == NULL) {
        return 0;
    }
    return trem(map->cols[idx], key);
}

void htdel(struct htmap *map) {
    for (int i = 0; i < map->cap; i++) {
        if (map->cols[i]) {
            tdel(map->cols[i]);
        }
    }
    free(map->cols);
    free(map);
}

#endif