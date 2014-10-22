#include "signals.h"

void
bye(int s)
{
	my_str("\nAN ERROR HAS OCCURRED: ");
	switch (s) {
	case SIGALRM:
		my_str("Request to server timed out.\n");
		break;
	case SIGINT:
		my_str("Application terminated prematurely.\n"); 
		break;
	default:
		my_str("Unknown signal status.\n");
	}

	exit(1);
}
