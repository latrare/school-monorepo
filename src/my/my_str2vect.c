#include "my.h"

/*
 * pre: given a non-NULL string
 * post: returns a vector representation of string (space/tab delimited array
 * of strings ending in null element)
 */
char **
my_str2vect(char *s)
{
	unsigned int i, j, k;
	char **nv;

	nv = NULL;
	if (s != NULL) {
		s = my_strdup(s); /* Needs to work on literal strings */
		for (i = 0, j = 0, k = 0; s[k] != '\0'; k++) {
			if ((k > 0 && (s[k - 1] != ' ' || s[k - 1] != '\t') &&
				(s[k] == ' ' || s[k] == '\t') && j != 1) ||
				(s[k + 1] == '\0' && (s[k] != ' ' || s[k] != '\t'))) {
				i++;
				j = 1;
				s[k++] = '\0';
			} else if (s[k] != ' ' || s[k] != '\t')
				j = 0;
		}
		nv = (char **)xmalloc(++i * sizeof(char *));
		for (k = i, i = 0, j = 0; i < k - 1; ) {
			if (s[j] != ' ' && s[j] != '\0') {
				nv[i++] = my_strdup(s + j);
				j += my_strlen(s + j);
			}
			j++;
		}
		nv[i] = NULL;
		free(s);
	}

	return (nv);
}
