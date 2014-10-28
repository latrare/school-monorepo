#include "sockets.h"

void
sv_cbye(int fd)
{
	if (fd == SIGINT) {
		close(cfd);
		close(sfd);
		exit(1);
	}
}
