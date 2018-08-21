//
// Created by Mohammad Yazdani on 8/20/18.
//

#ifndef S0_PAGE_H
#define S0_PAGE_H

#include <stdlib.h>
#include <stdint.h>

#define KEY_LEN 8

typedef struct data_page {
    size_t index_count;
    const int leaf;
    uintptr_t data;
    const char * key;
} page;

int page_create(page * new_page, const char key[KEY_LEN], uintptr_t value);
uintptr_t page_insert(page * p, const char key[KEY_LEN], uintptr_t item);
page * page_index(page * p, const char key[KEY_LEN]);
int page_destroy(page * p);
char * page_to_json(const page *p);


#endif //S0_PAGE_H
