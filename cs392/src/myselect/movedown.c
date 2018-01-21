#include "myselect.h"

/*
 * pre:
 * post:
 */
void
movedown()
{
	if (gl_env.pos < gl_env.nbelems - 1) {
		refreshout(gl_env.pos);
		gl_env.pos += 1;
		refreshin();
	}
}
