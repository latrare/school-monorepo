#include "my.h"

/*
 * pre: takes an integer
 * post: prints integer to stdout
 */
void
my_int(int n)
{
	long int in;
	unsigned long int power;

	in = n; /* Move n into larger type */
	my_char((n < 0) ? ('-') : ('\0'));
	in = (n < 0) ? (in * -1) : (in);

	for (power = 1; in / power >= 10; power *= 10);
	for (; power > 0; power /= 10)
		my_char('0' + ((in / power) % 10));
}
