#include "myselect.h"

/*
 * pre:
 * post:
 */
int
my_termprint(int c)
{
	return (write(1, &c, 1));
}
