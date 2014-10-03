#include "my.h"

/*
 * pre: takes two strings
 * post: returns pointer to destination string after copying source to destination
 */
char *
my_strcpy(char* s1, char* s2)
{
	int i;

	if (s1 != NULL && s2 != NULL) {
		for (i = 0; s1[i] != '\0'; i++)
			s1[i] = s2[i];
		s1[i] = '\0';
	}

	return (s1);
}
