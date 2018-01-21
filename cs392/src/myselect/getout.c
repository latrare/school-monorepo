#include "myselect.h"

/*
 * pre:
 * post:
 */
void
getout(char c)
{
	int i;

	term_clear();
	if (c) {
		restore_terminal();
		for (i = 0; i < gl_env.nbelems; i++) {
			if (gl_env.elements[i].mode) {
				my_str(gl_env.elements[i].elem);
				my_str(" ");
			}
		}
		my_str("\n");
	} else
		restore_terminal();

	exit(0);
}
