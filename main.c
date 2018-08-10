#include <stdio.h>
#include <fileio.h>
#include <strutil.h>
#include <stdlib.h>
#include <string.h>
#include <usr/iter_event.h>

int
main()
{
	fiter * test_io = read_csv_full("test.txt")->head->next;
	if (test_io == NULL) exit(1);

	long int data_size = 0, column_count = 0;

	char ** num_iter = parse_line(test_io->value, 3);
	data_size = strtol(num_iter[2], NULL, 10);
	printf("Data size: %ld\n", data_size);

	test_io = test_io->next;
	if (test_io == NULL) exit(1);

	char * column_data_copy = malloc(strlen(test_io->value) * sizeof(char));
	strcpy(column_data_copy, test_io->value);
	column_count = parse_line_wc(column_data_copy);
	free(column_data_copy);
	printf("Column count: %ld\n", column_count);

	test_io = test_io->next;
	int count = 0;
	while(test_io != NULL) {
		char ** line = parse_line(test_io->value, column_count);

		printf("  %d\n", count);
		count += 1;

		if (test_io == test_io->next) break;
		test_io = test_io->next;
	}

	printf("\nProcess finished normally.\n");
    return 0;
}
