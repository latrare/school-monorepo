#include "myselect.h"

/*
 * pre:
 * post:
 */
void
term_standend()
{
	tputs(gl_env.stand_end, 1, my_termprint);
}
