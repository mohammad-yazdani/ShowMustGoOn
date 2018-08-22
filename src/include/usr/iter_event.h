//
// Created by Mohammad Yazdani on 8/20/18.
//

#ifndef S0_ITER_EVENT_H
#define S0_ITER_EVENT_H

#include <stdint.h>
#include <page.h>
#include <io/fileio.h>

typedef struct iter_event {
	double loss;
	double reinstPrem;
	char riskGroup;
	double fullRip;
} iterevt;

uintptr_t create_iterevt(char * loss, char * reinstPrem, char * riskGroup, char * fullRip);

page * page_iter_data(fiter * iter_data, long int column_count);

page * load_events(const char * path);

#endif //S0_ITER_EVENT_H
