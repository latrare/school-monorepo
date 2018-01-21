#include "signals.h"

/*
 * pre: takes signal int
 * post: interprets client PID from signals
 */
void
getclpid(int s)
{
	if (s == SIGUSR1 || s == SIGUSR2)
		gl_env.clpid <<= 1;
	if (s == SIGUSR1)
		gl_env.clpid |= 1;
}
