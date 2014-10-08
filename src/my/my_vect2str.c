#include "my.h"

char *
my_vect2str(char **v)
{
	int i, slen, vlen;
	char *str;

	str = NULL;
	if (v != NULL && *v != NULL) {
		for (vlen = 0, slen = 0; v[vlen] != NULL; vlen++)
			slen += my_strlen(v[vlen]) + 1;
		str = (char *)xmalloc(slen);
		for (i = 0; i < vlen; i++) {
			str = my_strcat(str, v[i]);
			if (i < vlen - 1)
				str = my_strcat(str, " ");
		}
	}

	return (str);
}
