#include "myselect.h"

/*
 * pre:
 * post:
 */
void
term_clear()
{
	tputs(gl_env.clear, 1, my_termprint);
}
