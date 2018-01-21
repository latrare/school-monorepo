#include "my.h"

/*
 * pre: takes string (as char[])
 * post: reverses the given string in place and returns length of string
 */
int
my_revstr(char* s)
{
	int slen, i;
	char tmp;

	slen = -1;
	if (s != NULL) {
		slen = my_strlen(s);
		for (i = 0; i < slen / 2; i++) {
			tmp = s[i];
			s[i] = s[slen - i - 1];
			s[slen - i - 1] = tmp;
		}
	}

	return (slen);
}
