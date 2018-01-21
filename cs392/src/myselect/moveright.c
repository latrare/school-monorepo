#include "myselect.h"

/*
 * pre:
 * post:
 */
void
moveright()
{
	if (gl_env.pos < gl_env.nbelems - 1) {
		refreshout(gl_env.pos);
		if (gl_env.pos + gl_env.win.ws_row > gl_env.nbelems - 1)
			gl_env.pos = gl_env.nbelems - 1;
		else
			gl_env.pos += gl_env.win.ws_row;
		refreshin();
	}
}
