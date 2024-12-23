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

// Xoa 1 nut tren cay
int trem(struct tree *t, KEY key) {
    struct tnode *n = tsearch(t, key);
    if (!n) {
        return 0;
    }

    struct tnode *top = n->top;
    if (n->left == NULL && n->right == NULL) {
    /* TH1: n is leaf
        (n)
        / \
     NULL NULL
    */
        if (top) {
            if (n == top->left) {
                top->left = NULL;
            } else {
                top->right = NULL;
            }
        } else {
            t->root = NULL;
        }
        free(n);
        return 1;
    }

    struct tnode *r = n->right, *l = n->left;
    if (l == NULL) {
    /* TH2: n co 1 con
        (n)
        /  \
       NULL r
    */
        if (top == NULL) {
            t->root = r;
        } else {
            top->right = r;
        }
        r->top = top;
        free(n);
        return 1;
    }
    if (r == NULL) {
    /* TH2:
        (n)
        / \
       l  NULL
    */
        if (top == NULL) {
            t->root = l;
        } else {
            top->left = l;
        }
        l->top = top;
        free(n);
        return 1;
    }

    if (r->left == NULL) {
    /* TH3:
        (n)
        / \
      (x)  r
          /  \
        NULL (y)
    */
        r->left = n->left;
        n->left->top = r;
        if (top == NULL) {
            t->root = r;
        } else {
            if (top->left == n) {
                top->left = r;
            } else {
                top->right = r;
            }
        }
        r->top = top;
        free(n);
        return 1;
    }
    /* TH4:
        (n)
        / \
      (x)  r
          / \
        nn  (y)
       /  \
     NULL (z)
    */
    struct tnode *nn = r->left, *nnt = r;
    while (nn->left) {
        nnt = nn;
        nn = nn->left;
    }
    nnt->left = nn->right;
    if (nn->right) {
        nn->right->top = nnt;
    }
    nn->left = l;
    nn->right = r;
    l->top = nn;
    r->top = nn;
    if (top == NULL) {
        t->root = nn;
    } else {
        if (n == top->left) {
            top->left = nn;
        } else {
            top->right = nn;
        }
    }
    nn->top = top;
    free(n);
    return 1;
}

// Xoa toan bo nut va cay con cua no
void tdeln(struct tnode *node) {
    if (node == NULL) {
        return;
    }
    // Đệ quy xóa cây con trái và phải
    tdeln(node->left);
    tdeln(node->right);
    // Giải phóng nút hiện tại
    free(node);
}

// Xoa toan bo cay
void tdel(struct tree *t) {
    if (t == NULL || t->root == NULL) {
        return;
    }
    tdeln(t->root);
    free(t);
}


#endif