#include "signals.h"

/*
 * The server.
 * ---
 * Receives the PID of the client, acknowledges it, receives the client's
 * message, acknowledges receipt, ends connection.
 */
int
main()
{
	int i;

	gl_env = (t_gl_env){0}; /* Zeroing out struct */
	signal(SIGINT, bye);

	my_str("Server PID: ");
	my_int(getpid());
	my_str("\n-------------------\n");

	for (;;) {
		signal(SIGUSR1, getclpid);
		signal(SIGUSR2, getclpid);

		my_str("Waiting for client PID...\n");	
		for (i = 0; i < sizeof(pid_t) * 8; i++)
			pause();
		usleep(5000);
		kill(gl_env.clpid, SIGUSR1);

		my_str("Received client PID: ");
		my_int(gl_env.clpid);
		my_str("!\n");

		my_str("Waiting for message from ");
		my_int(gl_env.clpid);
		my_str("...\n");

		signal(SIGUSR1, getclchar);
		signal(SIGUSR2, getclchar);

		my_str("Receiving message from ");
		my_int(gl_env.clpid);
		my_str("...\n\n");
		while (!gl_env.done)
			pause();
		my_str("\n\n");
		my_str("Message received!\n");

		usleep(5000);
		kill(gl_env.clpid, SIGUSR1);
		gl_env.done = 0;
		my_str("Acknowledged client message.\n");
		my_str("----------------------------\n\n");
	}

	return (0);
}
