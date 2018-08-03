#include <stdlib.h>
#include <string.h>
#include <json.h>

char *
dq_wrap(const char * value)
{
	size_t org_len = strlen(value);
	char * wrapped = malloc((org_len + 2) * sizeof(char));
	strcat(wrapped, "\"");
	strcat(wrapped, value);
	strcat(wrapped, "\"");
	return wrapped;
}

char *
to_array_being(const char * value)
{
	size_t org_len = strlen(value);
	char * wrapped = malloc((org_len + 2) * sizeof(char));
	strcat(wrapped, "{\n");
	strcat(wrapped, value);
	return wrapped;
}

char *
to_array_end(const char * value)
{
	size_t org_len = strlen(value);
	char * wrapped = malloc((org_len + 2) * sizeof(char));
	strcat(wrapped, value);
	strcat(wrapped, "}\n");
	return wrapped;
}

char *
to_array_item(const char * value)
{
	size_t org_size = strlen(value);
	char * array_item = malloc((org_size + 2) * sizeof(char));
	strcat(array_item, value);
	strcat(array_item, ",\n");
	return array_item;
}

char *
create_assignment(const char * lvalue, const char * rvalue)
{
	char * lv_wrapped = dq_wrap(lvalue);
	char * rv_wrapped = dq_wrap(rvalue);

	size_t lvalue_len = strlen(lv_wrapped);
	size_t rvalue_len = strlen(rv_wrapped);

	char * assignment = malloc(
			(lvalue_len + rvalue_len + 3) * sizeof(char));
	strcat(assignment, lvalue);
	strcat(assignment, ":\n");
	strcat(assignment, rvalue);

	free(lv_wrapped);
	free(rv_wrapped);

	return assignment;
}

char * block_wrap(const char * value) {
	size_t org_len = strlen(value);
	char * wrapped = malloc((org_len + 4) * sizeof(char));
	strcat(wrapped, "{\n");
	strcat(wrapped, value);
	strcat(wrapped, "}\n");
	return wrapped;
}
