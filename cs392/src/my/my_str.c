#include "my.h"

/*
 * pre: takes string
 * post: outputs string to stdout
 */
void
my_str(char* s)
{
	if (s != NULL)
		for(; *s != '\0'; s++)
			my_char(*s);
}
