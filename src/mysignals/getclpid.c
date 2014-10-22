#include "signals.h"

void
getclpid(int s)
{
	if (s == SIGUSR1 || s == SIGUSR2)
		gl_env.clpid <<= 1;
	if (s == SIGUSR1)
		gl_env.clpid |= 1;
}
