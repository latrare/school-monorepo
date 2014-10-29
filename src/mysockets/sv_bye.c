#include "sockets.h"

/*
 * pre: handles termination signal events. Takes signal identifier int
 * post: does things based on signal identifier
 */
void
sv_bye(int sig)
{
	wait(NULL);
	if (sig == SIGINT)
		my_str("\nERROR: Server instance closed.\n");
	close(cfd);
	close(sfd);
	exit(1);
}
