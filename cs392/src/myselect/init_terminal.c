#include "myselect.h"

/*
 * pre:
 * post:
 */
void
init_terminal()
{
	int fd;
	char *name;
	struct termio mod;

	ioctl(0, TCGETA, &gl_env.line_backup);
	ioctl(0, TCGETA, &mod);
	mod.c_lflag &= ~(ICANON | ECHO | ISIG);
	mod.c_cc[VMIN] = READMIN;
	mod.c_cc[VTIME] = READTIME;
	ioctl(0, TCSETA, &mod);

	name = ttyname(0);
	fd = open(name, O_WRONLY);
	gl_env.stdio_backup = dup(1);
	dup2(fd, 1);

	gl_env.pos = 0;
}
