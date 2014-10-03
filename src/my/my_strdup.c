#include "my.h"

/*
 * pre: takes a string
 * post: returns new pointer to string with same content
 */
char *
my_strdup(char* s)
{
	int i;
	char *ns;

	ns = NULL;
	if (s != NULL) {
		ns = xmalloc(my_strlen(s) + 1);
		for (i = 0; s[i] != '\0'; i++)
			ns[i] = s[i];
		ns[i] = '\0';
	}

	return (ns);
}
