//
// Created by Mohammad Yazdani on 7/30/2018.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <json.h>
#include <page.h>
#include <strutil.h>

int
page_create(page * new_page, const char key[KEY_LEN], uintptr_t value)
{
	int is_leaf = 0;
	size_t size = 0;
	char * data = NULL;
	if (value) {
	    is_leaf = 1;
	    size = 1;
	    data = strdup((char *) value);
	}
	char * stored_key = malloc(KEY_LEN * sizeof(char));
	strcpy(stored_key, key);
    page page_init = { .index_count = size, .data = (uintptr_t) data, .leaf = is_leaf, .key = stored_key };

    memcpy(new_page, &page_init, sizeof(page));
    return 0;
}

uintptr_t
page_insert(page * p, const char key[KEY_LEN], uintptr_t item)
{
    page *new_page = NULL;
    int leaf = 0;
    char * local_key;
    if (key != NULL) {
        leaf = 1;
        local_key = (char *) key;
    }
    else {
        new_page = (page *) item;
        local_key = (char *) new_page->key;
    }
	page ** children = (page **) p->data;
	for (int i = 0; i < p->index_count; i++) {
		page * child = children[i];
		if (strcmp(local_key, child->key) == 0) {
			uintptr_t replaced_data = child->data;
			child->data = item;
			return replaced_data;
		}
	}

	int res;
	if (!leaf) {
        new_page = malloc(sizeof(page));
        res = page_create(new_page, local_key, item);
        if (res) exit(res);
	}

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
page_to_json(const page *p)
{
	char * dump_naked = NULL;
	if (p->index_count > 1) {
		page ** children = (page **) p->data;
		char ** children_data = malloc(p->index_count * sizeof(char *));
		size_t data_size = 0;

		for (int i = 0; i < p->index_count; i++) {
		    page * child = children[i];
			char * standalone_json = page_to_json(child);
			if (i == 0) {
				char * beginning_of_array = to_array_being(standalone_json);
				free(standalone_json);
				standalone_json = beginning_of_array;
			}
			if (i == p->index_count - 1) {
				char * end_of_array = to_array_end(standalone_json);
				free(standalone_json);
				children_data[i] = end_of_array;
			} else {
                children_data[i] = to_array_item(standalone_json);
                free(standalone_json);
			}

			data_size += strlen(children_data[i]);
		}

		char * rvalue = alloc_string(data_size);
		for (int i = 0; i < p->index_count; i++) {
			strcat(rvalue, children_data[i]);
			//free(children_data[i]);
		}

		dump_naked = create_assignment(dq_wrap(p->key), rvalue);
	} else {
		dump_naked = create_assignment(dq_wrap(p->key), dq_wrap((char *) p->data));
	}

	return dump_naked;
}
