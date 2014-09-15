#include "my.h"

/*
 * pre: takes a char
 * post: prints it to stdout
 */
void
my_char(char c)
{
	write(STDOUT_FILENO, &c, 1);
}
