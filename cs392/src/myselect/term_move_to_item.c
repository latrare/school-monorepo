#include "myselect.h"

/*
 * pre:
 * post:
 */
void
term_move_to_item(int pos)
{
	if (pos >= 0 && pos < gl_env.nbelems) {
		gl_env.pos = pos;
		term_move(gl_env.elements[pos].x, gl_env.elements[pos].y);
	}
}
