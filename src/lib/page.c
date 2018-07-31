//
// Created by Mohammad Yazdani on 7/30/2018.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "page.h"

int
page_create(page * new_page, const char key[KEY_LEN], uintptr_t data)
{
	int is_leaf = 0;
	if (data) is_leaf = 1;
    page page_init = { .index_count = 0, .data = data, .leaf = is_leaf, .key = key };
    memcpy(new_page, &page_init, sizeof(page));
    return 0;
}

uintptr_t
page_insert(page * p, const char key[KEY_LEN], uintptr_t item)
{
	page ** children = (page **) p->data;
	for (int i = 0; i < p->index_count; i++) {
		page * child = children[i];
		if (strcmp(key, child->key) == 0) {
			uintptr_t replaced_data = child->data;
			child->data = item;
			return replaced_data;
		}
	}

	page * new_page = malloc(sizeof(page));
	int res = page_create(new_page, key, item);
	if (res) exit(res);

	children = realloc(children, (p->index_count + 1) * sizeof(page *));
	children[p->index_count] = new_page;
	p->index_count += 1;

	return 0;
}

int
page_destroy(page * p)
{
	// TODO : Handle errors
	if (!p->leaf) {
		page ** children = (page **) p->data;
		for (int i = 0; i < p->index_count; i++) {
			page_destroy(children[i]);
		}
	}

	free((void *) p->data);
	free(p);
	return 0;
}

char *
page_dump(const page *p, size_t * size)
{
	char head[KEY_LEN + 7] = "";
    char suffix[] = " : {\n";

	char name_wrapped[11] = "";
	name_wrapped[0] = '"';
    strcat(name_wrapped, p->key);
    name_wrapped[9] = '"';
    name_wrapped[10] = '\0';

    strcat(head, name_wrapped);
    strcat(head, suffix);

	size_t dump_size = strlen(head);
    char * dump;

    if (p->leaf) {
    	dump_size += strlen((char *) p->data);
    	dump = malloc(sizeof(char) * (dump_size + 2));
    } else {
    	char ** children_data = malloc(sizeof(char *) * p->index_count);
    	page ** children = (page **) p->data;
    	for (int i = 0; i < p->index_count; i++) {
    		size_t child_size = 0;
    		children_data [i] = page_dump((const page *) children[i], &child_size);
    		dump_size += child_size;
    	}
    	
    	dump = malloc(sizeof(char) * (dump_size + 2));
    	strcat(dump, head);
    	for (int i = 0; i < p->index_count; i++) {
    		strcpy(dump, children_data[i]);
    	}
    }

    dump[dump_size] = '}';
    dump_size += 1;
    dump[dump_size] = '\0';

    *size = dump_size;
    return dump;
}
