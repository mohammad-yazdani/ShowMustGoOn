#include <string.h>
#include <stdbool.h>

char * dq_wrap(const char * value);
char * to_array_being(const char * value);
char * to_array_end(const char * value);
char * to_array_item(const char * value);
char * block_wrap(const char * value);

char * create_assignment(const char * lvalue, const char * rvalue);