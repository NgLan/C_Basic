#ifndef VECTOR_H
#define VECTOR_H

#ifndef VEC_ELEM_T
#define VEC_ELEM_T int // default type of elems of vector is int
#endif

#ifndef VEC_SCANF_FMT
#define VEC_SCANF_FMT "%d" // default scanf format is "%d"
#endif

#ifndef VEC_PRINTF_FMT
#define VEC_PRINTF_FMT "%d" // default printf format is "%d"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef VEC_ELEM_T vec_elem_t;

struct vector {
    int sz;
    int cap;
    vec_elem_t *elems;
};

#define VROF(v, cur) for(vec_elem_t *cur = (v)->elems; cur < (v)->elems + (v)->sz; cur++)

struct vector *vcreate(int n) {
    struct vector *v = (struct vector *)malloc(sizeof(struct vector));
    v->sz = n;
    v->cap = v->sz > 0 ? v->sz : 8;
    v->elems = (vec_elem_t *)calloc(v->cap, sizeof(vec_elem_t));
    return v;
}

void vreserve(struct vector *v, int newcap) {
    if (newcap <= v->sz) {
        return;
    }
    v->elems = (vec_elem_t *)realloc(v->elems, newcap*sizeof(vec_elem_t));
    if (v->cap < newcap) {
        memset(v->elems + v->cap, 0, sizeof(vec_elem_t)*(newcap));
    }
    v->cap = newcap; 
}

void vresize(struct vector *v, int newsize) {
    if (newsize > v->cap) {
        vreserve(v, newsize);
    }
    v->sz = newsize;
}

void vappend(struct vector *v, vec_elem_t value) {
    if (v->cap == 0) {
        vreserve(v, 16);
    } else if (v->sz == v->cap) {
        vreserve(v, 2*v->cap);
    }
    v->elems[v->sz] = value;
    v->sz++;
}

void vfree(struct vector *v) {
    if (!v) { // if vector v is empty then return
        return;
    } 
    free(v->elems);
    free(v);
}

void vscan_elem(vec_elem_t *e) {
    if (scanf(VEC_SCANF_FMT, e) != 1) {
        fprintf(stderr, "Input error!\n"); // check error
        exit(EXIT_FAILURE);
    }
}

void vprint_elem(vec_elem_t *e) {
    printf(VEC_PRINTF_FMT, e);
}

struct vector *vparse_nlist() {
    int n;
    scanf("%d", &n);
    struct vector *v = vcreate(n);
    VROF(v, cur) {
        vscan_elem(cur);
    }
    return v;
}

#endif