#include <stdio.h>
#include <fileio.h>
#include <strutil.h>

int
main()
{
	fiter * test_io = read_csv_full("test.txt")->head->next;
	int count = 0;
    while(test_io != NULL)
	{
		count += 1;
		parse_line(test_io->value);
		//printf("%s", test_io->value);
		test_io = test_io->next;
	}
    printf("Lines read: %d\n", count);
    return 0;
}
