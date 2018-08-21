//
// Created by Mohammad Yazdani on 8/20/18.
//

#ifndef S0_CONTRACT_H
#define S0_CONTRACT_H

#include <page.h>
#include <fileio.h>

typedef struct contract_object {
    char * contract_id;
} contract;

int contract_create(contract * collector, const char * contract_id);
int contract_destroy(contract * c);

page * page_contracts(fiter * cdata, long int column_count);
page * load_contracts(const char * path);

#endif //S0_CONTRACT_H
