#include "signals.h"

void
putclpid(pid_t clpid, pid_t svpid)
{
	int i, j;

	for (i = 0, j = 0; i < sizeof(pid_t) * 8; i++) { 
		usleep(5000);
		j = (clpid >> ((sizeof(pid_t) * 8) - (i + 1))) & 1;
		kill(svpid, (j) ? (SIGUSR1) : (SIGUSR2));
	}
}
