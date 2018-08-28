//
// Created by Mohammad Yazdani on 8/20/18.
//

#ifndef S0_STRUTIL_H
#define S0_STRUTIL_H

#include <stdlib.h>

char * alloc_string(size_t size);

int parse_line_wc(char * line);
char ** parse_line(char * line, int word_count);


#endif //S0_STRUTIL_H
