#include <stdlib.h>
#include <string.h>
#include <strutil.h>
#include <usr/iter_event.h>

#include <stdio.h>

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

page **
page_iter_data(fiter * iter_data, long int column_count)
{
	page ** pages = NULL;
	char * iter_id = NULL;
	page * curr_iter = NULL;

	while(iter_data != NULL) {
		char ** line = parse_line(iter_data->value, column_count);

		// Very inefficient, and what JS does.	
		if (iter_id == NULL) {
			iter_id = line[0];
			curr_iter = malloc(sizeof(page));
			int res = page_create(curr_iter, iter_id, 0);
			if (res) {
				// TODO : Unfold mem free
				// TODO : Free mem so far
				exit(res);
			}
		}
		else if (strcmp(iter_id, line[0]) == 0) {
			// Proccessing new iteration
			// TODO : Save prev iter
			printf("HAVE TO SAVE %d\n", (int) curr_iter);
			// TODO : Create new iter
			iter_id = line[0];
			curr_iter = malloc(sizeof(page));
			int res = page_create(curr_iter, iter_id, 0);
			if (res) {
				// TODO : Unfold mem free
				// TODO : Free mem so far
				exit(res);
			}

		}

		// TODO : Insert seq id, get lower object, insert event with value (if iter newly created)	
		page * seq_page = page_index(curr_iter, line[1]);
		if (seq_page == NULL) {
			// TODO : Create sequence object
			seq_page = malloc(sizeof(page));
			page_create(seq_page, line[1], 0);
		} else {

		}

		// TODO : Do the same for eventid

		if (iter_data == iter_data->next) break;
		iter_data = iter_data->next;
	}
	return NULL;
}
