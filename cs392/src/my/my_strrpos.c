#include "my.h"

/*
 * pre: takes string and character
 * post: returns position of last instance of the given character in the given
 * string; -1 if NULL or not found
 */
int
my_strrpos(char* s, char c)
{
	int i, pos;

	pos = -1;
	if (s != NULL) {
		for (i = 0, pos = -1; *s != '\0'; i++, s++)
			if (*s == c)
				pos = i;
	}

	return (pos);
}
