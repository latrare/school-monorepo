#include "my.h"

/*
 * pre: two strings
 * post: returns pointer to new string that is two given strings concatenated
 */
char *
my_strcat(char* s1, char* s2)
{
	int i;
	char *ns;
	
	if (s1 != NULL && s2 != NULL) {
		ns = (char *)xmalloc(my_strlen(s1) + my_strlen(s2) + 1);
		for (i = 0; s1[i] != '\0'; i++)
			ns[i] = s1[i];
		ns[i] = '\0';
	} else if (s1 != NULL && s2 == NULL)
		return (s1);
	else
		return (NULL);

	return (ns);
}
