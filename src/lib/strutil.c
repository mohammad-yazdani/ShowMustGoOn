//
// Created by yazda on 2018-08-03.
//

#include <stdlib.h>
#include <strutil.h>
#include <string.h>
#include <stdio.h>

char *
alloc_string(const size_t size)
{
    char * direct_mem = malloc(size * sizeof(char));
    for (int i = 0; i < size; i++) {
        direct_mem[i] = 0;
    }
    return direct_mem;
}

int 
parse_line_wc(char * line)
{
	char * word_iter = strtok(line, "\t ,.-");
	int count = 0;
	while (word_iter != NULL)
	{
		word_iter = strtok (NULL, "\t ,.-");
		count += 1;
	}

    return count;
}

char **
parse_line(char * line, const int word_count)
{
	char ** words = malloc(word_count * sizeof(char *));
	char * word_iter = strtok(line, "\t ,.-");

	int count = 0;
	while (word_iter != NULL && count < word_count)
	{
		words[count] = word_iter;
		word_iter = strtok (NULL, "\t ,.-");
		count += 1;
	}

    return words;
}
