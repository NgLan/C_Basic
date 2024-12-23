#ifndef BST_H
#define BST_H

#ifndef KEY
#define KEY int
#endif

#ifndef VALUE_T
#define VALUE_T long
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode {
    KEY key;
    VALUE_T value;
    struct tnode *left, *right, *top;
};

struct tree {
    struct tnode *root;
    long size;
};

struct tnode *tnode(KEY key, VALUE_T value) {
    struct tnode *n = (struct tnode *)malloc(sizeof(struct tnode));
    n->key = key;
    n->value = value;
    n->left = n->right = n->top = NULL;
    return n;
}

struct tree *tree() {
    struct tree *t = (struct tree *)malloc(sizeof(struct tree));
    t->root = NULL;
    t->size = 0;
    return t;
}

int compare(KEY a, KEY b) {
    if (a == b) return 0;
    else if (a > b) return 1;
    else return -1;
}

struct tnode *tput(struct tree *t, KEY key, VALUE_T value) {
    struct tnode *top = NULL, *n = t->root;
    int order;
    while (n) {
        order = compare(key, n->key);
        if (order == 0) { // Neu co key trong cay roi thi thoi
            return n;
        }
        top = n;
        n = order < 0 ? n->left : n->right;
    }
    n = tnode(key, value);
    n->top = top;
    t->size++;
    if (top == NULL) {
        t->root = n;
        return NULL;
    }
    if (order < 0) {
        top->left = n;
    } else {
        top->right = n;
    }
    return NULL;
}

struct tnode *left_most(struct tnode *n) {
    struct tnode *top = NULL;
    while (n) {
        top = n;
        n = n->left;
    }
    return top;
}

// Ham tra ve phan tu nho nhat ma lon hon n theo thu tu in order
struct tnode *next(struct tnode *n) {
    if (n->right) {
        return left_most(n->right);
    }
    while (n->top) {
        if (n->top->left == n) {
            return n->top;
        }
        n = n->top;
    }
    return NULL;
}

struct tnode *tsearch(struct tree *t, KEY key) {
    struct tnode *n = t->root;
    while (n) {
        int o = compare(key, n->key);
        if (o == 0) {
            return n;
        }
        n = o < 0 ? n->left : n->right;
    }
    return NULL;
}

#endif