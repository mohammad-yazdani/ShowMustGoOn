//
// Created by Mohammad Yazdani on 7/30/2018.
//

#ifndef SIMORGH_PAGE_H
#define SIMORGH_PAGE_H

#include <stdlib.h>
#include <stdint.h>

#define KEY_LEN 8

struct
data_page {
    size_t index_count;
    const int leaf;
    uintptr_t data;
    const char * key;
};
typedef struct data_page page;

int page_create(page * new_page, const char key[KEY_LEN], uintptr_t data);
uintptr_t page_insert(page * p, const char key[KEY_LEN], uintptr_t item);
int page_destroy(page * p);
char * page_dump(const page *p, size_t * size);

#endif //SIMORGH_PAGE_H
