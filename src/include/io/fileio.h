//
// Created by Mohammad Yazdani on 8/20/18.
//

#ifndef S0_FILEIO_H
#define S0_FILEIO_H

#include <stdlib.h>

#define ITER_LINE_LEN 125
#define LAYTERS_LINE_LEN 500

typedef struct file_iterator {
	unsigned long pos;
	char * value;
	struct file_iterator * next;
	struct file_iterator * head;
} fiter;


fiter * fiter_add(fiter * iter, char * value);

fiter * read_csv_full(const char * fullpath, unsigned long line_len);
int write_json(const char * fullpath, const char * buf);


#endif //S0_FILEIO_H
