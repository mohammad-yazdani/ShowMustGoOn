#include <stdint.h>
#include <page.h>
#include <fileio.h>

typedef struct iter_event {
	double loss;
	double reinstPrem;
	char riskGroup;
	double fullRip;
} iterevt;

uintptr_t create_iterevt(char * loss, char * reinstPrem, char * riskGroup, char * fullRip);

page ** page_iter_data(fiter * iter_data, long int column_count); 
