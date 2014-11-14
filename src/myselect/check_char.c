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
			if (my_strcmp(c, KU) == 0)
				moveup();
			else if (my_strcmp(c, KD) == 0)
				movedown();
			else if (my_strcmp(c, KL) == 0)
				moveleft();
			else if (my_strcmp(c, KR) == 0)
				moveright();
			else if (my_strcmp(c, " ") == 0)
				doselect();
		} else {
			if (my_strcmp(c, "\E") == 0)
				getout((char)0);
			else if (my_strcmp(c, "\n") == 0)
				getout((char)1);
		}
	}
}
