#include "myselect.h"

/*
 * pre:
 * post:
 */
void
term_vi()
{
	tputs(gl_env.cursoroff, 1, my_termprint);
}
