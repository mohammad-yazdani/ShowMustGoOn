//
// Created by Mohammad Yazdani on 8/20/18.
//

#include <queue.h>
#include <string.h>
#include <stdlib.h>

int
queue_create(queue * collector)
{
    queue q = { .size = 0, .head = NULL, .tail = NULL };
    memcpy(collector, &q, sizeof(queue));
    return 0;
}

int
queue_destroy(queue * q)
{
    if (!q->size) {
        linked * curr = q->head;
        while (curr != NULL) {
            free((void *) curr->data);
            linked * old = curr;
            curr = curr->next;
            free(old);
        }
    }

    free(q);
    return 0;
}

uintptr_t
queue_pop(queue * q)
{
    linked * head = q->head;
    if (head == NULL) return 0;
    if (head->next != NULL) exit(2);
    q->head = head->back;
    if (q->head) q->head->next = NULL;
    uintptr_t data = head->data;
    free(head);

    q->size -= 1;
    return data;
}

int
queue_push(queue * q, uintptr_t data)
{
    linked * new_item = malloc(sizeof(linked));
    new_item->back = NULL;
    new_item->next = q->tail;
    new_item->data = data;

    if (q->tail) q->tail->back = new_item;
    q->tail = new_item;
    if (q->size == 0) q->head = new_item;

    q->size += 1;
    return 0;
}