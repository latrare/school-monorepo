#include "my.h"

/*
 * pre: takes string
 * post: returns length of string or -1 if NULL
 */
int
my_strlen(char* s)
{
	unsigned int slen;

	if (s != NULL) {
		for (slen = 0; *s != '\0'; slen++, s++);
		return (slen);
	}

	return (-1);
}
