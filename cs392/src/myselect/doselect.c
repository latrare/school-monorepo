#include "myselect.h"

/*
 * pre:
 * post:
 */
void
doselect()
{
	gl_env.elements[gl_env.pos].mode ^= 1;
	refreshin();
}
