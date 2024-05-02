#include "jrb.h"
#include <stdlib.h>

JRB make_jrb() {
    JRB tree = (JRB)malloc(sizeof(struct jrb_node));
    tree->parent = tree->flink = tree->blink = NULL;
    tree->red = 0;
    tree->key = tree->val = NULL;
    return tree;
}

JRB jrb_insert_str(JRB tree, char *key, void *val) {
    JRB new_node = make_jrb();
    new_node->key = strdup(key);
    new_node->val = val;
    JRB temp, prev = NULL;
    temp = tree->flink;

    while (temp != NULL) {
        prev = temp;
        temp = strcmp(key, (char *)temp->key) < 0 ? temp->blink : temp->flink;
    }

    new_node->parent = prev;
    if (prev == NULL) {
        tree->flink = new_node;
    } else {
        if (strcmp(key, (char *)prev->key) < 0)
            prev->blink = new_node;
        else
            prev->flink = new_node;
    }

    return new_node;
}

JRB jrb_insert_int(JRB tree, int key, void *val) {
    JRB new_node = make_jrb();
    new_node->key = (void *)(intptr_t)key;
    new_node->val = val;
    JRB temp, prev = NULL;
    temp = tree->flink;

    while (temp != NULL) {
        prev = temp;
        temp = key < (int)(intptr_t)temp->key ? temp->blink : temp->flink;
    }

    new_node->parent = prev;
    if (prev == NULL) {
        tree->flink = new_node;
    } else {
        if (key < (int)(intptr_t)prev->key)
            prev->blink = new_node;
        else
            prev->flink = new_node;
    }

    return new_node;
}

JRB jrb_insert_dbl(JRB tree, double key, void *val) {
    JRB new_node = make_jrb();
    new_node->key = (void *)(intptr_t)key;
    new_node->val = val;
    JRB temp, prev = NULL;
    temp = tree->flink;

    while (temp != NULL) {
        prev = temp;
        temp = key < (double)(intptr_t)temp->key ? temp->blink : temp->flink;
    }

    new_node->parent = prev;
    if (prev == NULL) {
        tree->flink = new_node;
    } else {
        if (key < (double)(intptr_t)prev->key)
            prev->blink = new_node;
        else
            prev->flink = new_node;
    }

    return new_node;
}

void *jrb_find_str(JRB tree, char *key) {
    JRB temp = tree->flink;
    while (temp != NULL) {
        int cmp = strcmp(key, (char *)temp->key);
        if (cmp == 0) return temp->val;
        temp = cmp < 0 ? temp->blink : temp->flink;
    }
    return NULL;
}

void *jrb_find_int(JRB tree, int key) {
    JRB temp = tree->flink;
    while (temp != NULL) {
        int cmp = key - (int)(intptr_t)temp->key;
        if (cmp == 0) return temp->val;
        temp = cmp < 0 ? temp->blink : temp->flink;
    }
    return NULL;
}

void *jrb_find_dbl(JRB tree, double key) {
    JRB temp = tree->flink;
    while (temp != NULL) {
        double cmp = key - (double)(intptr_t)temp->key;
        if (cmp == 0) return temp->val;
        temp = cmp < 0 ? temp->blink : temp->flink;
    }
    return NULL;
}

void jrb_delete_node(JRB node) {
    if (node->flink != NULL && node->blink != NULL) {
        JRB pred = jrb_pred(node);
        jrb_replace(node, pred);
        node = pred;
    }

    if (node->flink != NULL) {
        node->flink->parent = node->parent;
        if (node == node->parent->flink) node->parent->flink = node->flink;
        else node->parent->blink = node->flink;
    } else if (node->blink != NULL) {
        node->blink->parent = node->parent;
        if (node == node->parent->flink) node->parent->flink = node->blink;
        else node->parent->blink = node->blink;
    } else {
        if (node == node->parent->flink) node->parent->flink = NULL;
        else node->parent->blink = NULL;
    }

    free(node->key);
    free(node);
}

JRB jrb_find_gte_str(JRB tree, char *key) {
    JRB temp = tree->flink;
    JRB result = NULL;

    while (temp != NULL) {
        int cmp = strcmp(key, (char *)temp->key);
        if (cmp <= 0) {
            result = temp;
            temp = temp->blink;
        } else {
            temp = temp->flink;
        }
    }

    return result;
}

JRB jrb_find_gte_int(JRB tree, int key) {
    JRB temp = tree->flink;
    JRB result = NULL;

    while (temp != NULL) {
        int cmp = key - (int)(intptr_t)temp->key;
        if (cmp <= 0) {
            result = temp;
            temp = temp->blink;
        } else {
            temp = temp->flink;
        }
    }

    return result;
}

JRB jrb_find_gte_dbl(JRB tree, double key) {
    JRB temp = tree->flink;
    JRB result = NULL;

    while (temp != NULL) {
        double cmp = key - (double)(intptr_t)temp->key;
        if (cmp <= 0) {
            result = temp;
            temp = temp->blink;
        } else {
            temp = temp->flink;
        }
    }

    return result;
}

void jrb_free_tree(JRB tree) {
    JRB temp = tree->flink;
    while (temp != NULL) {
        JRB next = temp->blink;
        free(temp->key);
        free(temp);
        temp = next;
    }
    free(tree);
}
