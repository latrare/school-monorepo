#include "sockets.h"

void
cl_bye(int sfd)
{
	char *bye;

	if (sfd == SIGINT) {
		bye = "/exit\n";
		if (write(fd, bye, 256) < 0)
			my_str("\nERROR: Failed to send exit transmission.\n");
		my_str("\nERROR: Client instance closed.\n");
	} else if (sfd == SIGALRM)
		my_str("\nERROR: Server connection timed out.\n");
	close(fd);
	exit(1);
}
