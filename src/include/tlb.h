//
// Created by Mohammad Yazdani on 8/28/18.
//

#ifndef S0_TLB_H
#define S0_TLB_H

#include "page.h"

typedef struct trans_entry {
    char * key;
    uintptr_t value;
    int dirty;
} entry;

typedef struct trans_cache {
    size_t cap;
    size_t size;
    entry * entries;
} tlb;

static tlb * TLB = NULL;

int tlb_init(size_t init_size);
int tlb_full_flush();
int tlb_flush(entry * flushee);
int tlb_clear(entry * ent);
char * tlb_get(const char * key);
int tlb_push(const char * key, const char * value);

#endif //S0_TLB_H
