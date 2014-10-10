#include "my.h"

/*
 * pre: given vector (string array terminated by NULL element)
 * post: return string representation (space delimited)
 */
char *
my_vect2str(char **v)
{
	int i, slen, vlen;
	char *str;

	str = NULL;
	if (v != NULL) {
		for (vlen = 0, slen = 0; v[vlen] != NULL; vlen++)
			slen += my_strlen(v[vlen]) + 1;
		str = vlen > 0 ? (char *)xmalloc(slen) : NULL;
		for (i = 0; i < vlen; i++) {
			str = my_strcat(str, v[i]);
			if (i < vlen - 1)
				str = my_strcat(str, " ");
		}
	}

	return (str);
}
