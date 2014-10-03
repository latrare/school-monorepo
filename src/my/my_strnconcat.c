#include "my.h"

/*
 * pre: takes two strings and unsigned int
 * post: returns pointer to concatenation of n letters of second string on to first
 */
char *
my_strnconcat(char* s1, char* s2, unsigned int n)
{
	int i, j;
	char *ns;

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
		for (j = 0; s2[j] != '\0' && n > 0; i++, j++, --n)
			ns[i] = s2[j];
	ns[i] = '\0';

	return (ns);
}
