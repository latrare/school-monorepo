#include "myselect.h"

/*
 * pre:
 * post:
 */
void
moveup()
{
	if (gl_env.pos > 0) {
		refreshout(gl_env.pos--);
		refreshin();
	}
}
