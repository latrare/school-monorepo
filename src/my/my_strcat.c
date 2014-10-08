#include "my.h"

/*
 * pre: two strings
 * post: returns pointer to new string that is two given strings concatenated
 */
char *
my_strcat(char* s1, char* s2)
{
	int i;

	if (s1 != NULL && s2 != NULL) {
		i = my_strlen(s1);
		for (; *s2 != '\0'; s2++, i++)
			s1[i] = *s2;
		s1[i] = '\0';
	}

	return (s1);
}
