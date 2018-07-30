//
// Created by Mohammad Yazdani on 7/30/2018.
//

#ifndef SIMORGH_PAGE_H
#define SIMORGH_PAGE_H

#include <stdlib.h>
#include <stdint.h>

#define NAME_LENGTH 8

struct
data_page {
    size_t size;
    uintptr_t * children;
    const int type;
    const char * name;
};
typedef struct data_page page;

int page_create(page * new_page, int type, const char name[NAME_LENGTH]);
int page_insert(page * p, uintptr_t item);
int page_destroy(page * p);
char * page_dump(const page *p, size_t * size);

#endif //SIMORGH_PAGE_H
