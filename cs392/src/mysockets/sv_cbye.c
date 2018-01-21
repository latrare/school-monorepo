#include "sockets.h"

/*
 * pre: child process termination event signal handler; takes signal int
 * post: exits child and closes resources for child process
 */
void
sv_cbye(int fd)
{
	if (fd == SIGINT) {
		close(cfd);
		close(sfd);
		exit(1);
	}
}
