#include "my.h"

/*
 * pre: takes two strings and unsigned int
 * post: returns comparison of first string to n letters of the second string
 */
int
my_strncmp(char* s1, char* s2, unsigned int n)
{
	if (s1 != NULL && s2 != NULL) {
		for (; n > 0; s1++, s2++, --n) {
			if (*s1 != *s2) {
				if (*s1 > *s2)
					return (1);
				else
					return (-1); 
			} else if (*s1 == '\0')
				return (0);
		}
		return (0);
	} else if (s1 == NULL && s2 == NULL)
		return (0);
	else if (s1 != NULL && s2 == NULL)
		return (1);
	else
		return (-1);

	return (-1);
}
