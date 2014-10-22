#include "signals.h"

/*
 * pre: takes a signal int
 * post: sets the gl_env_ack variable to 1 if s is SIGUSR1
 */
void
ack(int s)
{
	if (s == SIGUSR1)
		gl_env_ack = 1;
}
