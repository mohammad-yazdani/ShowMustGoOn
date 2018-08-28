//
// Created by Mohammad Yazdani on 8/20/18.
//

#ifndef S0_JSON_H
#define S0_JSON_H

#include <string.h>
#include <stdbool.h>

char * dq_wrap(const char * value);
char * to_array_begin(const char * value);
char * to_array_end(const char * value);
char * to_array_item(const char * value);
char * block_wrap(const char * value);
char * create_assignment(const char * lvalue, const char * rvalue);

char * unwrap(const char * value);
char * dq_unwrap(const char * value);
char ** extract_values(const char * value, size_t * size);
int extract_assignment(const char * assignment, char ** lvalue, char ** rvalue);

#endif //S0_JSON_H
