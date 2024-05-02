#ifndef JRB_H
#define JRB_H

#include <string.h> // for strdup
#include <stdint.h> // for intptr_t

typedef struct jrb_node {
    unsigned char red;
    struct jrb_node *parent;
    struct jrb_node *flink;
    struct jrb_node *blink;
    void *key;
    void *val;
} *JRB;

JRB make_jrb();
JRB jrb_insert_str(JRB tree, char *key, void *val);
JRB jrb_insert_int(JRB tree, int key, void *val);
JRB jrb_insert_dbl(JRB tree, double key, void *val);
void *jrb_find_str(JRB tree, char *key);
void *jrb_find_int(JRB tree, int key);
void *jrb_find_dbl(JRB tree, double key);
void jrb_delete_node(JRB node);
JRB jrb_find_gte_str(JRB tree, char *key);
JRB jrb_find_gte_int(JRB tree, int key);
JRB jrb_find_gte_dbl(JRB tree, double key);
void jrb_free_tree(JRB tree);

#endif
