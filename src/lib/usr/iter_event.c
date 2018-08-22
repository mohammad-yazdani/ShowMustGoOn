#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <util/strutil.h>
#include <usr/iter_event.h>

// TODO : Rename [ALL] based on standard

uintptr_t
create_iterevt(char * loss, char * reinstPrem, char * riskGroup, char * fullrip)
{
	iterevt * iter_obj = malloc(sizeof(iterevt));

	iter_obj->loss = strtod(loss, NULL);
	iter_obj->reinstPrem = strtod(reinstPrem, NULL);
	iter_obj->fullRip = strtod(fullrip, NULL);
	iter_obj->riskGroup = riskGroup[0];

	return (uintptr_t) iter_obj;
}

// TODO : This is where the streaming beings
page *
page_iter_data(fiter * iter_data, long int column_count)
{
    char * iter_id = NULL;
	page * curr_iter = NULL;

	page * surface = malloc(sizeof(page));
	int pres = page_create(surface, "root", 0);
	if (pres) exit(pres);

	while(iter_data != NULL) {
		char ** line = parse_line(iter_data->value, (const int) column_count);

		// Very inefficient, but important to the research
		if (iter_id == NULL) {
			iter_id = line[0];
			curr_iter = malloc(sizeof(page));
			int res = page_create(curr_iter, iter_id, 0);
			if (res) {
				free(curr_iter);
				page_destroy(surface);
				exit(res);
			}
		}
		else if (strcmp(iter_id, line[0]) != 0) {
			// Processing new iteration
			// Save prev iter
			uintptr_t popped = page_insert(surface, NULL, (uintptr_t) curr_iter);
			if (popped) {
				printf("ERROR: Replacing events is not permitted.\n");
				exit(EPERM);
			}
			printf("HAVE TO SAVE %s\n", curr_iter->key);

			// Create new iter
			iter_id = line[0];
			curr_iter = malloc(sizeof(page));
			int res = page_create(curr_iter, iter_id, 0);
			if (res) {
				free(curr_iter);
				page_destroy(surface);
				exit(res);
			}
		}

		page * seq_page = page_index(curr_iter, line[1]);
		if (seq_page == NULL) {
			seq_page = malloc(sizeof(page));
			page_create(seq_page, line[1], 0);
			page_insert(curr_iter, NULL, (uintptr_t) seq_page);
		}

		uintptr_t iter_obj = create_iterevt(line[3], line[4], line[5], line[6]);
		page_insert(seq_page, line[2], iter_obj);

		if (iter_data == iter_data->next) break;
		iter_data = iter_data->next;
	}
	return surface;
}

// TODO : Or the streaming begins here?
page *
load_events(const char * path)
{
	fiter * test_io = read_csv_full(path, ITER_LINE_LEN)->head->next;
	if (test_io == NULL) exit(1);

	long int column_count = 0;

	char ** num_iter = parse_line(test_io->value, 3);
	strtol(num_iter[2], NULL, 10);

	test_io = test_io->next;
	if (test_io == NULL) exit(1);

	char * column_data_copy = malloc(strlen(test_io->value) * sizeof(char));
	strcpy(column_data_copy, test_io->value);
	column_count = parse_line_wc(column_data_copy);
	free(column_data_copy);

	test_io = test_io->next;

    page * extracted_data = page_iter_data(test_io, column_count);
	return extracted_data;
}
