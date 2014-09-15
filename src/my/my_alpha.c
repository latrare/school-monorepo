#include "my.h"

/*
 * pre: n/a
 * post: prints every letter of the English alphabet
 */
void
my_alpha()
{
	char i;

	for (i = 'A'; i <= 'Z'; i++) {
		my_char(i);
		my_char(i + 32);
	}
}
