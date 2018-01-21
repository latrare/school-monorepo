#include "my.h"

/*
 * pre: takes string and character
 * post: returns position of first instance of the given character in the given
 * string; -1 if NULL or not found
 */
int
my_strpos(char* s, char c)
{
	int i;

	if (s != NULL)
		for (i = 0; *s != '\0'; s++, i++)
			if (*s == c)
				return (i);

	return (-1);
}
