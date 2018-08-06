#include <stdio.h>
#include <fileio.h>

int
main()
{
	fiter * test_io = read_csv_full("test.csv")->head->next;
	while(test_io != NULL)
	{
		printf("%s", test_io->value);
		test_io = test_io->next;
	}
    return 0;
}
