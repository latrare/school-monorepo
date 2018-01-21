#include "my.h"

/*
 * pre: takes a string and a character
 * post: returns pointer to character (last occurence) in string
 */
char *
my_strrfind(char* s, char c)
{
	int pos;

	pos = my_strrpos(s, c);

	return ((pos >= 0) ? (s + pos) : (NULL));
}
