#include <fileio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
read_csv_full(const char * fullpath)
{
	FILE * fp;
	fp = fopen (fullpath, "r");

	unsigned long fsize;

	fseek (fp , 0 , SEEK_END);
	fsize = ftell (fp);
	rewind (fp);

	char buff[LINE_LEN], * result;
	// TODO : Handle ENOMEM
	//int res = fread(buff, 1, fsize, fp);
	//(void)res;
	// TODO : Handle read err (res != fsize)
	
	fiter * file_data = malloc(sizeof(fiter));
	file_data->head = file_data;
	file_data->next = NULL;
	file_data->pos = 0;
	file_data->value = NULL;
	
	while((result = fgets(buff, LINE_LEN, fp)) != NULL)
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
