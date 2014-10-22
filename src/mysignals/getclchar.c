#include "signals.h"

void
getclchar(int s)
{
	static int i = 0;
	static char c = 0;

	if (s == SIGUSR1 || s == SIGUSR2) {
		c <<= 1;
		if (s == SIGUSR1)
			c |= 1;
		if (++i >= (sizeof(char) * 8)) {
			my_char(c);
			if (c == '\0')
				gl_env.done = 1;
			i = 0;
			c = 0;
		}
	}
}
