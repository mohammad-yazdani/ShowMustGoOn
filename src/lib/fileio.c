#include <fileio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

fiter *
fiter_add(fiter * iter, char * value)
{
	fiter * new_item = malloc(sizeof(fiter));
	new_item->head = iter->head;
	new_item->next = NULL;
	new_item->pos = (iter->pos + 1);
	new_item->value = malloc(strlen(value) * sizeof(char));
	strcpy(new_item->value, value);

	iter->next = new_item;

	return new_item;
}

fiter * 
read_csv_full(const char * fullpath, unsigned long line_len)
{
	FILE * fp;
	fp = fopen (fullpath, "r");

	unsigned long fsize;

	fseek (fp , 0 , SEEK_END);
	fsize = (unsigned long) ftell (fp);
	rewind (fp);

	char buff[line_len], * result;
	
	fiter * file_data = malloc(sizeof(fiter));
	if (file_data == NULL) exit(ENOMEM);
	file_data->head = file_data;
	file_data->next = NULL;
	file_data->pos = 0;
	file_data->value = NULL;
	
	int count = 0;
	while((result = fgets(buff, line_len, fp)) != NULL)
	{
		file_data = fiter_add(file_data, result);
	}

	fclose(fp);
	return file_data;
}

int
write_json(const char * fullpath, const char * buf)
{
	return 0;
}
