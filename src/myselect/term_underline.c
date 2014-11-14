#include "myselect.h"

/*
 * pre:
 * post:
 */
void
term_underline()
{
	tputs(gl_env.underline, 1, my_termprint);
}
