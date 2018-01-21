#include "my.h"

void
my_freevect(char **v)
{
	int i;
	
	if (v != NULL) {
		for (i = 0; v[i] != NULL; i++)
			free(v[i]);
		free(v);
	}
}
