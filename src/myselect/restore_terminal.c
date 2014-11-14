#include "myselect.h"

/*
 * pre:
 * post:
 */
void
restore_terminal()
{
	term_ve();
	ioctl(0, TCSETA, &gl_env.line_backup);
	dup2(gl_env.stdio_backup, 1);
	free(gl_env.elements);
}
