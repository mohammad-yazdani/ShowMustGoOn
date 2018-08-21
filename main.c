#include <stdio.h>
#include <usr/contract.h>
#include <usr/iter_event.h>

int
main()
{
	printf("Running ...\n");
	page * contracts = load_contracts("../data/layers.txt");
	char * json = page_to_json(contracts);
	printf("%s\n", json);
	load_events("../data/test.txt");
    return 0;
}
