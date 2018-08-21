//
// Created by Mohammad Yazdani on 8/20/18.
//

#ifndef S0_LINKED_H
#define S0_LINKED_H

#include <stdint.h>

typedef struct linked_list {
    uintptr_t data;
    struct linked_list * back;
    struct linked_list * next;
} linked;

#endif //S0_LINKED_H
