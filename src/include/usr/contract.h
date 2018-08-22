//
// Created by Mohammad Yazdani on 8/20/18.
//

#ifndef S0_CONTRACT_H
#define S0_CONTRACT_H

#include <page.h>
#include <io/fileio.h>
#include <queue.h>

typedef struct contract_object {
    char * contract_id;
} contract;

int contract_create(contract * collector, const char * contract_id);
int contract_destroy(contract * c);


queue * enqueue_contracts(fiter * cdata, long int column_count);
queue * load_contracts(const char * path);

#endif //S0_CONTRACT_H
