#include "my.h"

/*
 * pre: takes a string and character to find
 * post: returns pointer to character in string
 */
char *
my_strfind(char* s, char c)
{
	int pos;

	pos = my_strpos(s, c);

	return ((pos >= 0) ? (s + pos) : (NULL));
}
