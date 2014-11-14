#include "myselect.h"

/*
 * pre:
 * post:
 */
void
term_ve()
{
	tputs(gl_env.cursoron, 1, my_termprint);
}
