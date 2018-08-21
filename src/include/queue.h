//
// Created by Mohammad Yazdani on 8/20/18.
//

#ifndef S0_QUEUE_H
#define S0_QUEUE_H

#include <stdint.h>
#include <stdlib.h>
#include "linked.h"

typedef struct object_queue {
    linked * head;
    linked * tail;
    size_t size;
} queue;

int queue_create(queue * collector);
int queue_destroy(queue * q);
uintptr_t queue_pop(queue * q);
int queue_push(queue * q, uintptr_t data);

#endif //S0_QUEUE_H
