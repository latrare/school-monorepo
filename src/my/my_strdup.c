#include "my.h"

char *
my_strdup(char* s)
{
	char *new;

	new = NULL;
	if (s != NULL) {
		new = xmalloc(my_strlen(s) + 1);
		do {
			*new = *s;
			new++;
			s++;
		} while (*s != '\0');
	}

	return (new);
}
