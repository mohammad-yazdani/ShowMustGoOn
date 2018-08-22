//
// Created by Mohammad Yazdani on 8/20/18.
//

#include <contract.h>
#include <string.h>
#include <util/strutil.h>

int
contract_create(contract * collector, const char * contract_id)
{
    contract contract_temp = { .contract_id = alloc_string(strlen(contract_id))};
    memcpy(collector, &contract_temp, sizeof(contract));
    strcpy(collector->contract_id, contract_id);
    return 0;
}

int
contract_destroy(contract * c)
{
    free(c->contract_id);
    free(c);
    return 0;
}

contract *
contract_load(const char ** src)
{
    const char * contract_id = src[0];

    contract * c = malloc(sizeof(contract));
    int res = contract_create(c, contract_id);
    if (res) exit(res);

    return c;
}

queue *
enqueue_contracts(fiter * cdata, long int column_count)
{
    queue * q = malloc(sizeof(queue));
    int res = queue_create(q);
    if (res) exit(res);

    if (cdata == NULL) exit(1);

    while(cdata != NULL) {
        char ** line = parse_line(cdata->value, (const int) column_count);

        contract * c = contract_load((const char **) line);
        queue_push(q, (uintptr_t) c);

        if (cdata == cdata->next) break;
        cdata = cdata->next;
    }
    return q;
}

queue *
load_contracts(const char * path)
{
    fiter * test_io = read_csv_full(path, LAYTERS_LINE_LEN)->head->next;
    if (test_io == NULL) exit(1);

    long int column_count = 0;

    char * column_data_copy = malloc(strlen(test_io->value) * sizeof(char));
    strcpy(column_data_copy, test_io->value);
    column_count = parse_line_wc(column_data_copy);
    free(column_data_copy);

    test_io = test_io->next;

    queue * extracted_data = enqueue_contracts(test_io, column_count);
    return extracted_data;
}