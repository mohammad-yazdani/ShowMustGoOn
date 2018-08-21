#include <stdio.h>
#include <usr/contract.h>
#include <usr/iter_event.h>

int
main()
{
	printf("Running ...\n");

	queue * contracts = load_contracts("../data/layers.txt");

	contract * c = (contract *) queue_pop(contracts);
	while (c != NULL) {
	    printf("%s\n", c->contract_id);
	    c = (contract *) queue_pop(contracts);
	}

	load_events("../data/test.txt");
    return 0;
}
