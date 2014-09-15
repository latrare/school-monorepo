#include "my.h"

int
my_strcmp(char* s1, char* s2)
{
	for (; *s1 != '\0' && *s2 != '\0'; s1++, s2++) {
		if (*s2 < *s1)
			return (-1);
		if (*s2 > *s1)
			return (1);
	}

	return (0);
}
