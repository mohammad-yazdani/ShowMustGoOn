#include <stdlib.h>

#define LINE_LEN 123

typedef struct file_iterator {
	unsigned long pos;
	char * value;
	struct file_iterator * next;
	struct file_iterator * head;
} fiter;


fiter * fiter_add(fiter * iter, char * value);

fiter * read_csv_full(const char * fullpath);
int write_json(const char * fullpath, const char * buf);
