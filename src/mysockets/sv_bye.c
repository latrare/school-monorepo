#include "sockets.h"

void
sv_bye(int fd)
{
	wait(NULL);
	if (fd == SIGINT)
		my_str("\nERROR: Server instance closed.\n");
	close(cfd);
	close(sfd);
	exit(1);
}
