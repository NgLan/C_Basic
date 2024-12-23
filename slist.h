#ifndef SLIST_H
#define SLIST_H

#ifndef SLIST_ELEM_T
#define SLIST_ELEM_T int
#endif

#include <stdlib.h>
#include <string.h>

#define SFOR(cur, list) \
    for (struct snode *cur = list->head; cur != NULL; cur = cur->next)

struct snode {
    SLIST_ELEM_T elem;
    struct snode *next;
};


struct slist
{
    struct snode *head, *tail;
    int len;
};

struct snode *snode(SLIST_ELEM_T elem) {
    struct snode *n = (struct snode *)malloc(sizeof(struct snode));
    n->elem = elem;
    n->next = NULL;
    return n;
}

struct slist *slist() {
    struct slist *list = (struct slist *)malloc(sizeof(struct slist));
    list->len = 0;
    list->head = list->tail = NULL;
    return list;
}

struct slist *sappend(struct slist *list, SLIST_ELEM_T elem) {
    struct snode *n = snode(elem);
    if (list->tail == NULL) {
        list->head = list->tail = n;
        list->len = 1;
        return list;
    }
    list->tail->next = n;
    list->tail = n;
    list->len++;
    return list;
}

struct slist *sprepend(struct slist *list, SLIST_ELEM_T elem) {
    struct snode *n = snode(elem);
    if (list->head == NULL) {
        list->head = list->tail = n;
        list->len = 1;
        return list;
    }
    n->next = list->head;
    list->head = n;
    list->len++;
    return list;
}

struct slist *sdelh(struct slist *list) {
    //De nguoi dung tu kiem tra dieu kien head = NULL
    struct snode *tmp = list->head->next;
    free(list->head);
    list->head = tmp;
    list->len--;
    if (list->len == 0) {
        list->tail = NULL;
    }
    return list;
}

struct snode *top(struct slist *list) {
    return list->head;
}
 
struct snode *peek(struct slist *list) {
    return list->head;
}

// Stack: push & pop
// Queue: push_back & pop
struct slist *pop(struct slist *list) {
    return sdelh(list);
}

struct slist *push(struct slist *list, SLIST_ELEM_T elem) {
    return sprepend(list, elem);
}

struct slist *push_back(struct slist *list, SLIST_ELEM_T elem) {
    return sappend(list, elem);
}

int isEmpty(struct slist *list) {
	if (list->tail == NULL || list->head == NULL || list->len == 0) return 1;
	return 0;
}

void sdel(struct slist *list) {
    struct snode *n = list->head;
    while (n)
    {
        struct snode *tmp = n->next;
        free(n);
        n = tmp;
    }
    free(list);
}

#endif