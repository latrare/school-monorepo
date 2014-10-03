#include "my.h"

/*
 * pre: takes integer and string of digit characters
 * post: outputs integer in base represented by string of digit characters
 */
void
my_num_base(int n, char* d)
{
	int b;
	unsigned int pwr, absi;

	b = my_strlen(d);
	if (d != NULL && b > 0) {
		if (n < 0)
			my_char('-');
		absi = (n < 0) ? ((long int)n * -1) : ((long int)n);
		if (b > 1) {
			for (pwr = 1; absi / pwr >= b; pwr *= b)
				;
			for (; pwr > 0; pwr /= b)
				my_char(d[(absi / pwr) % 10]);
		} else
			for (; absi > 0; absi--, my_char(d[0]))
				;
	} else
		my_str("Base not valid.\n");
}
