#include "my.h"

/*
 * pre: takes two strings
 * post: returns pointer of first string with the second string moved into it
 */
char *
my_strconcat(char* s1, char* s2)
{
	int i, j;
	char *ns;

	/* This function assumes that the given s1 is properly allocated */
	if (s1 != NULL && s2 != NULL)
		ns = (char *)xmalloc(my_strlen(s1) + my_strlen(s2) + 1);
	else if (s1 == NULL && s2 != NULL)
		ns = (char *)xmalloc(my_strlen(s2) + 1);
	else if (s1 != NULL && s2 == NULL)
		ns = (char *)xmalloc(my_strlen(s1) + 1);
	else
		return (NULL);

	i = 0;
	if (s1 != NULL)
		for (; s1[i] != '\0'; i++)
			ns[i] = s1[i];
	if (s2 != NULL)
		for (j = 0; s2[j] != '\0'; i++, j++)
			ns[i] = s2[j];
	ns[i] = '\0';

	return (ns);
}
