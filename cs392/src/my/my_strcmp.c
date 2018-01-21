#include "my.h"

/*
 * pre: given two strings
 * post: return comparison of first string (alphabetically) to second string
 */
int
my_strcmp(char* s1, char* s2)
{
	if (s1 != NULL && s2 != NULL) {
		for (; *s1 == *s2; s1++, s2++)
			if (*s1 == '\0')
				return (0);
		if (*s1 > *s2)
			return (1);
	} else if (s1 == NULL && s2 == NULL)
		return (0);
	else if (s1 != NULL && s2 == NULL)
		return (1);
	else
		return (-1);

	return (-1);
}
