#include "myselect.h"

/*
 * pre:
 * post:
 */
void
term_move(int x, int y)
{
	tputs(tgoto(gl_env.move, x, y), 1, my_termprint);
}
