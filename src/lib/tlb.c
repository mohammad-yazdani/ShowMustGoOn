//
// Created by Mohammad Yazdani on 8/28/18.
//

#include <string.h>
#include <tlb.h>
#include <sqlite3.h>
#include <io/db.h>

int tlb_find(const char * key);
int tlb_rand();

int
tlb_init(size_t init_size)
{
    tlb initializer = { .cap = init_size, .size = 0, .entries = malloc(init_size * sizeof(entry)) };
    if (TLB != NULL) {
        free(TLB);
        TLB = NULL;
    }
    TLB = malloc(sizeof(tlb));
    memcpy(TLB, &initializer, sizeof(tlb));
    return 0;
}

int
tlb_flush(entry * flushee)
{
    int res = 0;

    if (flushee->dirty) {
        char * check = db_find(flushee->key);

        if (check != NULL) {
            res = db_update(flushee->key, (const char *) flushee->value);
        } else {
            res = db_insert(flushee->key, (const char *) flushee->value);
        }

        if (res) {
            db_close();
            exit(res);
        }
    }

    return 0;
}

int
tlb_clear(entry * ent)
{
    if (ent->key != NULL) {
        free(ent->key);
        ent->key = NULL;
    }
    if (ent->value != 0) {
        free((void *) ent->value);
        ent->value = 0;
    }
    return 0;
}

int
tlb_full_flush()
{
    int res;
    for (int i = 0; i < TLB->cap; i++) {
        res = tlb_flush(&TLB->entries[i]);
        if (res) exit(res);
    }

    return 0;
}

int
tlb_push(const char * key, const char * value)
{
    int new_index = tlb_find(key);
    int res = 0;

    if (new_index != -1) {
        res = tlb_flush(&TLB->entries[new_index]);
        if (res) exit(res);
        res = tlb_clear(&TLB->entries[new_index]);
        if (res) exit(res);
        TLB->entries[new_index].dirty = 1;
    } else if (TLB->size == TLB->cap) {
        new_index = tlb_rand();
        res = tlb_flush(&TLB->entries[new_index]);
        if (res) exit(res);
        res = tlb_clear(&TLB->entries[new_index]);
        if (res) exit(res);
        TLB->entries[new_index].dirty = 1;
    } else {
        new_index = (int) TLB->size;
        TLB->size += 1;
        TLB->entries[new_index].dirty = 0;
    }

    TLB->entries[new_index].key = (char *) key;
    TLB->entries[new_index].value = (uintptr_t) value;

    return 0;
}

char *
tlb_get(const char * key)
{
    int index = tlb_find(key);
    if (index == -1) return NULL;
    return (char *) TLB->entries[index].value;
}

int
tlb_find(const char * key)
{
    for (int i = 0; i < TLB->size; i++) {
        char * cur_key = TLB->entries[i].key;
        if (strcmp(cur_key, key) == 0) {
            return i;
        }
    }
    return -1;
}

int
tlb_rand()
{
    return (int) (random() % TLB->size);
}
