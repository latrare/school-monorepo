#include "my.h"

/*
 * pre: takes two strings
 * post: returns pointer of first string with the second string moved into it
 */
char *
my_strconcat(char* s1, char* s2)
{
	int i;
	char *ns;

	ns = NULL;
	if (s1 != NULL && s2 != NULL) {
		i = 0;
		if (s1 != NULL)
			for (; *s1 != '\0'; s1++, i++)
				ns[i] = *s1;
		if (s2 != NULL)
			for (; *s2 != '\0'; s2++, i++)
				ns[i] = *s2;
		ns[i] = '\0';
	}

	return (ns);
}
