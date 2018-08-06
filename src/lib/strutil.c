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

char **
parse_line(char * line)
{
	char * words;
	words = strtok(line, "\t ,.-");

	while (words != NULL)
	{
		printf ("%s\n", words);
		words = strtok (NULL, "\t ,.-");
	}

    return 0;
}
