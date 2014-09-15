#include "my.h"

/*
 * pre: takes integer and string of digit characters
 * post: outputs integer in base represented by string of digit characters
 */
void
my_num_base(int n, char* d)
{
	unsigned int b, i;
	unsigned long int exp, tmp;

	b = my_strlen(d);
	if (d != NULL && b > 0) {
		tmp = n;
		my_char((n < 0) ? ('-') : ('\0'));
		tmp = (n < 0) ? (tmp * -1) : (tmp);
		if (b > 1) {
			for (i = 0, exp = 1; exp < tmp; i++, exp *= b);
			for (exp /= b; exp >= 1; exp /= b) {
				my_char(d[(tmp / exp)]);
				tmp -= ((tmp / exp) * exp);
			}
		} else
			for (; tmp > 0; tmp--, my_char(d[0]));
	} else
		my_str("Base not valid.\n");
}
