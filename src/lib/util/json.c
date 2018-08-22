#include <stdlib.h>
#include <string.h>
#include <util/json.h>
#include <util/strutil.h>

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
to_array_being(const char * value)
{
	size_t org_len = strlen(value);
	char * wrapped = alloc_string(org_len + 3);
	strcat(wrapped, "{ ");
	strcat(wrapped, value);
	return wrapped;
}

char *
to_array_end(const char * value)
{
	size_t org_len = strlen(value);
	char * wrapped = alloc_string(org_len + 3);
	strcat(wrapped, value);
	strcat(wrapped, "} ");
	return wrapped;
}

char *
to_array_item(const char * value)
{
	size_t org_size = strlen(value);
	char * array_item = alloc_string(org_size + 3);
	strcat(array_item, value);
	strcat(array_item, ", ");
	return array_item;
}

char *
create_assignment(const char * lvalue, const char * rvalue)
{
	size_t lvalue_len = strlen(lvalue);
	size_t rvalue_len = strlen(rvalue);

	char * assignment = alloc_string(lvalue_len + rvalue_len + 3);
	strcat(assignment, lvalue);
	strcat(assignment, ": ");
	strcat(assignment, rvalue);

	return assignment;
}

char * block_wrap(const char * value) {
	size_t org_len = strlen(value);
	char * wrapped = alloc_string(org_len + 4);
	strcat(wrapped, "{ ");
	strcat(wrapped, value);
	strcat(wrapped, "} ");
	return wrapped;
}
