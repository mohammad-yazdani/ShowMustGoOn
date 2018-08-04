//
// Created by yazda on 2018-08-03.
//

#include "strutil.h"

char *
alloc_string(const size_t size)
{
    char * direct_mem = malloc(size * sizeof(char));
    for (int i = 0; i < size; i++) {
        direct_mem[i] = 0;
    }
    return direct_mem;
}