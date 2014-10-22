#include "signals.h"

void
putclchar(char c, pid_t svpid)
{
	int i, j;

	for (i = 0, j = 0; i < sizeof(char) * 8; i++) {
		usleep(5000);
		j = (c >> ((sizeof(char) * 8) - (i + 1))) & 1;
		kill(svpid, (j) ? (SIGUSR1) : (SIGUSR2));
	}
}
