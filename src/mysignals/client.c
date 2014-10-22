#include "signals.h"

/*
 * The client.
 * ---
 * Sends its PID over to the server, server acknowledges, client sends message,
 * server receives message, acknowleges it received message, connection ends.
 */
int
main(int argc, char **argv)
{
	int i;
	pid_t clpid, svpid;
	char *str;

	if (argc < 3 || my_atoi(argv[1]) < 0) {
		my_str("Usage: ./client SERVER_PID MESSAGE\n");
		exit(1);
	}
	
	gl_env_ack = 0; /* Zeroing out gl_env_ack */
	signal(SIGINT, bye);
	signal(SIGALRM, bye);
	signal(SIGUSR1, ack);
	clpid = getpid();
	svpid = (pid_t)my_atoi(argv[1]);

	my_str("Client PID: ");
	my_int((int)clpid);
	my_str(" --> Server PID: ");
	my_int((int)svpid);
	my_str("\n-----------------------------------------\n");

	my_str("Sending client PID...\n");
	putclpid(clpid, svpid);
	if (!gl_env_ack) {
		alarm(5);
		pause();
	}
	alarm(0);
	gl_env_ack = 0;
	my_str("Client PID acknowledged!\n");

	str = my_vect2str(&argv[2]);
	my_str("Message prepared: \"");
	my_str(str);

	my_str("\"\nSending message...\n");
	for (i = 0; str[i] != '\0'; i++)
		putclchar(str[i], svpid);
	putclchar('\0', svpid);
	my_str("Finished sending message!\n");

	if (!gl_env_ack) {
		alarm(5);
		pause();
	}
	alarm(0);
	gl_env_ack = 0;
	my_str("Client message acknowledged.\n");

	return (0);
}
