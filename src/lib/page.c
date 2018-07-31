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

	if (p->index_count == 0) children = malloc((p->index_count + 1) * sizeof(page *));
	else children = realloc(children, (p->index_count + 1) * sizeof(page *));
	
	children[p->index_count] = new_page;
	p->index_count += 1;
	p->data = (uintptr_t) children;

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
	char head[KEY_LEN + 5] = "";
    char suffix[] = " : ";

	char name_wrapped[11] = "\"";
    strcat(name_wrapped, p->key);
    strcat(name_wrapped, "\"");

    strcat(head, name_wrapped);
    strcat(head, suffix);

	size_t dump_size = strlen(head);
    char * dump = malloc(dump_size * sizeof(char));
    strcpy(dump, head);

    if (p->leaf) {
    	dump_size += strlen((char *) p->data) + 1;
    	dump = realloc(dump, sizeof(char) * dump_size);
    	strcat(dump, (char *) p->data);
    } else {
    	size_t obj_size = 0;
    	char ** children_data = malloc(sizeof(char *) * p->index_count);
    	page ** children = (page **) p->data;
    	for (int i = 0; i < p->index_count; i++) {
    		size_t child_size = 0;
    		children_data [i] = page_dump((const page *) children[i], &child_size);
    		obj_size += child_size;
    	}
    	
    	size_t data_offset = dump_size;
    	dump_size += obj_size + 2;
    	dump = realloc(dump, sizeof(char) * (dump_size + (p->index_count - 1)));
    	dump[data_offset] = '{';
    	for (int i = 0; i < p->index_count; i++) {
    		strcat(dump, children_data[i]);
    		if (i + 1 < p->index_count) {
    			strcat(dump, ",");
    		}
    	}
    	strcat(dump, "}");
    }

    *size = dump_size;
    return dump;
}
