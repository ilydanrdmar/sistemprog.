#include "dlist.h"
#include <stdlib.h>

Dlist new_dlist() {
    Dlist d = (Dlist)malloc(sizeof(struct Dlnode));
    d->flink = d;
    d->blink = d;
    return d;
}

void dlist_insert_b(Dlist node, Jval val) {
    Dlist newnode = (Dlist)malloc(sizeof(struct Dlnode));
    newnode->val = val;
    newnode->flink = node;
    newnode->blink = node->blink;
    newnode->flink->blink = newnode;
    newnode->blink->flink = newnode;
}

void dlist_insert_a(Dlist n, Jval val) {
    dlist_insert_b(n->flink, val);
}

void dlist_append(Dlist l, Jval val) {
    dlist_insert_b(l, val);
}

void dlist_prepend(Dlist l, Jval val) {
    dlist_insert_b(l->flink, val);
}

void dlist_delete_node(Dlist node) {
    node->flink->blink = node->blink;
    node->blink->flink = node->flink;
    free(node);
}

int dlist_is_empty(Dlist l) {
    return (l->flink == l);
}

int dlist_length(Dlist l) {
    int len = 0;
    Dlist tmp = l->flink;
    while (tmp != l) {
        len++;
        tmp = tmp->flink;
    }
    return len;
}

Jval dlist_first(Dlist l) {
    if (dlist_is_empty(l)) return new_jval_v(NULL);
    return l->flink->val;
}

Jval dlist_last(Dlist l) {
    if (dlist_is_empty(l)) return new_jval_v(NULL);
    return l->blink->val;
}

Dlist dlist_find(Dlist l, Jval val) {
    Dlist tmp = l->flink;
    while (tmp != l) {
        if (tmp->val.i == val.i) return tmp;
        tmp = tmp->flink;
    }
    return NULL;
}

void free_dlist(Dlist l) {
    while (!dlist_is_empty(l)) {
        dlist_delete_node(l->flink);
    }
    free(l);
}
