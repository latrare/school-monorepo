#include "signals.h"

void
ack(int s)
{
	if (s == SIGUSR1)
		gl_env_ack = 1;
}
