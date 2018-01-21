#include "sockets.h"

/*
 * pre: signal handler for program termination takes signal int
 * post: executes instructions based on signal int
 */
void
cl_bye(int sig)
{
	char *bye;

	if (sig == SIGINT) {
		bye = "/exit\n";
		if (write(fd, bye, 7) < 0)
			my_str("\nERROR: Failed to send exit transmission.\n");
		my_str("\nERROR: Client instance closed.\n");
	} else if (sig == SIGALRM)
		my_str("\nERROR: Server connection timed out.\n");
	close(fd);
	exit(1);
}
