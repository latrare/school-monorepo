#include "myselect.h"

/*
 * pre:
 * post:
 */
void
check_char(char *c)
{
	if (c != NULL) {
		if (gl_env.flag != 1) {
			if (!my_strcmp(c, KU))
				moveup();
			else if (!my_strcmp(c, KD))
				movedown();
			else if (!my_strcmp(c, KL))
				moveleft();
			else if (!my_strcmp(c, KR))
				moveright();
			else if (!my_strcmp(c, " "))
				doselect();
		} else {
			if (!my_strcmp(c, "\E"))
				getout((char)0);
			else if(!my_strcmp(c, "\n"))
				getout((char)1);
		}
	}
}
