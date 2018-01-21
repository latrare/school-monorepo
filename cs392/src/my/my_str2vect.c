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
		for (i = 0, j = 0; s[i] != '\0'; i++) {
			if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n') {
				j = 1;
				break;
			}
		}
		if (j != 0) {
			for (j = 0; s[i] != '\0'; i++) {
				if (i > 0 && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n') && (s[i - 1] != ' ' && s[i - 1] != '\t' && s[i - 1] != '\n')) {
					s[i++] = '\0';
					j++;
				}
			}
			if (i > 0 && s[i] == '\0' && (s[i - 1] != ' ' && s[i - 1] != '\t' && s[i - 1] != '\n'))
				j++;
			if (i > 1 && s[i - 1] == '\n' && (s[i - 2] != ' ' && s[i - 2] != '\t' && s[i - 2] != '\n'))
				j++;
			nv = (char **)xmalloc(j * sizeof(char *));
			for (k = j, i = 0, j = 0; i < k - 1;) {
				if (s[j] != '\0' && s[j] != ' ' && s[j] != '\t' && s[j] != '\n') {
					nv[i++] = my_strdup(s + j);
					j += my_strlen(s + j);
				}
				j++;
			}
			nv[i] = NULL;
		}
		free(s);
	}

	return (nv);
}
