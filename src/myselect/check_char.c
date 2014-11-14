#include "myselect.h"

/*
 * pre:
 * post:
 */
void
check_char(char *c)
{
	if (c != NULL) {
		if (my_strcmp(c, KU) == 0 && gl_env.flag != 1)
			moveup();
		else if (my_strcmp(c, KD) == 0 && gl_env.flag != 1)
			movedown();
		else if (my_strcmp(c, KL) == 0 && gl_env.flag != 1)
			moveleft();
		else if (my_strcmp(c, KR) == 0 && gl_env.flag != 1)
			moveright();
		else if (my_strcmp(c, " ") == 0 && gl_env.flag != 1)
			doselect();
		else if (my_strcmp(c, "\E") == 0)
			getout(0);
		else if (my_strcmp(c, "\n") == 0)
			getout(1);
	}
}
