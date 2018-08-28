#include <stdlib.h>
#include <string.h>
#include <util/json.h>
#include <util/strutil.h>
#include <stdio.h>

char *
dq_wrap(const char * value)
{
	size_t org_len = strlen(value);
	char * wrapped = alloc_string(org_len + 3);
	strcat(wrapped, "\"");
	strcat(wrapped, value);
	strcat(wrapped, "\"");
	return wrapped;
}

char *
to_array_begin(const char * value)
{
	size_t org_len = strlen(value);
	char * wrapped = alloc_string(org_len + 3);
	strcat(wrapped, "{");
	strcat(wrapped, value);
	return wrapped;
}

char *
to_array_end(const char * value)
{
	size_t org_len = strlen(value);
	char * wrapped = alloc_string(org_len + 3);
	strcat(wrapped, value);
	strcat(wrapped, "}");
	return wrapped;
}

char *
to_array_item(const char * value)
{
	size_t org_size = strlen(value);
	char * array_item = alloc_string(org_size + 3);
	strcat(array_item, value);
	strcat(array_item, ",");
	return array_item;
}

char *
create_assignment(const char * lvalue, const char * rvalue)
{
	size_t lvalue_len = strlen(lvalue);
	size_t rvalue_len = strlen(rvalue);

	char * assignment = alloc_string(lvalue_len + rvalue_len + 3);
	strcat(assignment, lvalue);
	strcat(assignment, ":");
	strcat(assignment, rvalue);

	return assignment;
}

char * block_wrap(const char * value) {
	size_t org_len = strlen(value);
	char * wrapped = alloc_string(org_len + 4);
	strcat(wrapped, "{");
	strcat(wrapped, value);
	strcat(wrapped, "}");
	return wrapped;
}

char *
unwrap(const char * value)
{
    if (value[0] != '{') return (char *) value;
    size_t size = strlen(value);
    char * new_value = alloc_string(size);
    memmove(new_value, value, size - 1);
    memmove(new_value, new_value + 1, strlen(new_value));
    return new_value;
}

char *
dq_unwrap(const char * value)
{
    if (value[0] != '\"') return (char *) value;
    size_t size = strlen(value);
    char * new_value = alloc_string(size);
    memmove(new_value, value, size - 1);
    memmove(new_value, new_value + 1, strlen(new_value));
    return new_value;
}

char **
extract_values(const char * value, size_t * size)
{
    if (strchr(value, ',') == NULL) return NULL;

    *size = 0;
    char ** collector = NULL;

    char * copy = strdup(value);
    int offset = 0;
    int ctrl = 0;
    for (int i = 0;  i < strlen(value); i++) {
        char curr_head = value[i];
        if (curr_head == '{') ctrl += 1;
        else if (curr_head == '}') {
            if (ctrl > 0) ctrl -= 1;
            else exit(2);
        } else if (curr_head == ',') {
            if (ctrl == 0) {
                int anchor = i - offset;
                if (copy[anchor - 1] == ',') anchor -= 1;
                char * item = alloc_string((size_t) anchor);
                memcpy(item, copy, anchor);

                size_t old_size = strlen(copy);
                memmove(copy, copy + anchor + 1, old_size - anchor);

                offset = i;
                (*size) += 1;
                if (collector ==  NULL) collector = malloc((*size) * sizeof(char *));
                else collector = realloc(collector, (*size) * sizeof(char *));
                collector[(*size) - 1] = item;
            }
        }
    }

    int anchor = (int) ((strlen(value) - 1) - offset);
    if (copy[anchor - 1] == ',') anchor -= 1;
    char * item = alloc_string((size_t) anchor);
    memcpy(item, copy, anchor);

    free(copy);

    (*size) += 1;
    if (collector ==  NULL) collector = malloc((*size) * sizeof(char *));
    else collector = realloc(collector, (*size) * sizeof(char *));
    collector[(*size) - 1] = item;

    return collector;
}

int
extract_assignment(const char * assignment, char ** lvalue, char ** rvalue)
{
    char * word_iter = strtok((char *) assignment, ":");
    *lvalue = word_iter;
    word_iter = strtok(NULL, "");
    if (word_iter == NULL) return 0;
    memmove(word_iter, word_iter + 1, strlen(word_iter));
    size_t rval_size = strlen(word_iter);
    memmove(word_iter, word_iter, rval_size - 1);
    word_iter[rval_size - 1] = 0;
    *rvalue = word_iter;
    return 0;
}