#ifndef DLIST_H
#define DLIST_H

#include "jval.h"

typedef struct Dlnode {
    Jval val;
    struct Dlnode *flink;
    struct Dlnode *blink;
} *Dlist;

Dlist new_dlist();              // Yeni bir çift yönlü bağlı liste oluşturur
void dlist_insert_b(Dlist, Jval);  // Belirtilen düğümün öncesine bir düğüm ekler
void dlist_insert_a(Dlist, Jval);  // Belirtilen düğümün sonrasına bir düğüm ekler
void dlist_append(Dlist, Jval);    // Listeye bir düğüm ekler
void dlist_prepend(Dlist, Jval);   // Listeye bir düğüm ekler
void dlist_delete_node(Dlist);     // Belirtilen düğümü siler
int dlist_is_empty(Dlist);         // Liste boş mu kontrol eder
int dlist_length(Dlist);           // Listenin uzunluğunu hesaplar
Jval dlist_first(Dlist);           // Listenin ilk elemanını döndürür
Jval dlist_last(Dlist);            // Listenin son elemanını döndürür
Dlist dlist_find(Dlist, Jval);     // Belirtilen değeri içeren düğümü bulur
void free_dlist(Dlist);            // Listenin belleğini serbest bırakır

#endif
