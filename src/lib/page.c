//
// Created by Mohammad Yazdani on 7/30/2018.
//

#include <string.h>
#include <stdio.h>
#include "page.h"

int
page_create(page * new_page, const int type, const char name[NAME_LENGTH])
{
    page page_init = { .size = 0, .children = NULL, .type = type, .name = name };
    memcpy(new_page, &page_init, sizeof(page));
    return 0;
}

int
page_insert(page * p, const uintptr_t item)
{
    p->children = realloc(p->children, (p->size + 1) * sizeof(uintptr_t));
    p->children[p->size] = item;
    p->size += 1;
    return 0;
}

int
page_destroy(page * p)
{
    if (p->type < 2) {
        for (int i = 0; i < p->size; i++) {
            page_destroy((page *) p->children[i]);
        }
        free(p->children);
    }
    free(p);
    return 0;
}

char *
page_dump(const page *p, size_t * size)
{
    char head[NAME_LENGTH + 5] = " : {\0";
    strcat(head, p->name);
    size_t dump_size = strlen(head);
    printf(head);

    char * dump;
    if (p->type < 2) {
        char ** children_data = malloc(sizeof(char *) * p->size);

        for (int i = 0; i < p->size; i++) {
            size_t child_size = 0;
            children_data [i] = page_dump((const page *) p->children[i], &child_size);
        }

        dump = malloc(sizeof(char) * (dump_size + 2));
        strcat(dump, head);

        for (int i = 0; i , p->size; i++) {
            strcpy(dump, children_data[i]);
        }
    } else {
        dump = malloc(sizeof(char) * (dump_size + 2));
    }

    dump[dump_size] = '}';
    dump_size += 1;
    dump[dump_size] = '\0';

    *size = dump_size;
    return dump;
}
