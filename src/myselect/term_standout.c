#include "myselect.h"

/*
 * pre:
 * post:
 */
void
term_standout()
{
	tputs(gl_env.standout, 1, my_termprint);
}
