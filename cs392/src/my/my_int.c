#include "my.h"

/*
 * pre: takes an integer
 * post: prints integer to stdout
 */
void
my_int(int n)
{
	unsigned int pwr, absi;

	if (n < 0)
		my_char('-');
	absi = (n < 0) ? ((long int)n * -1) : ((long int)n);
	for (pwr = 1; absi / pwr >= 10; pwr *= 10)
		;
	for (; pwr > 0; pwr /= 10)
		my_char('0' + ((absi / pwr) % 10));
}
