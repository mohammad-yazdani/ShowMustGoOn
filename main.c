#include <stdio.h>
#include <usr/iter_event.h>

int
main()
{
	load_events("./iter-event-loss-portfolio.txt");
	printf("Running Simorgh...\n");
    return 0;
}
