#include "myselect.h"

/*
 * pre:
 * post:
 */
void
moveleft()
{
	if (gl_env.pos > 0) {
		refreshout(gl_env.pos);
		if (gl_env.pos - gl_env.win.ws_row < 0)
			gl_env.pos = 0;
		else
			gl_env.pos -= gl_env.win.ws_row;
		refreshin();
	}
}
