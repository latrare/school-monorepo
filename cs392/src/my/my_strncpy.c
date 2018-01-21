#include "my.h"

/*
 * pre: takes two strings and unsigned int
 * post: returns pointer to first string after n letters of second string are moved over
 */
char *
my_strncpy(char* s1, char* s2, unsigned int n)
{
	int i;

	if (s1 != NULL && s2 != NULL) {
		for (i = 0; s1[i] != '\0' && n > 0; i++, --n)
			s1[i] = s2[i];
	}

	return (s1);
}
