#include <stdio.h>
#include <usr/iter_event.h>

int
main()
{
	printf("Running Simorgh...\n");
	load_events("./iter-event-loss-portfolio.txt");
    return 0;
}
