#define _H_CLIENT_

#include "sockets.h"

/*
 * The client.
 * ---
 *  Identifies itself by send the input username.
 *  Can send text to the server, which the server displays.
 *  Commands /nick (to change handle), /me (to RP), and /exit (to exit)
 *  	are supported.
 */
int
main(int argc, char **argv)
{
	int n;
	char *buff, *username, **args;
	struct hostent *shost;
	struct sockaddr_in saddr;

	if (argc != 3 || my_atoi(argv[2]) < 1 || my_atoi(argv[2]) > (2 << 15) - 1) {
		my_str("usage: ./client SERVER_NAME SERVER_PORT\n");
		exit(1);
	}

	signal(SIGINT, cl_bye);
	signal(SIGALRM, cl_bye);

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		my_str("\nERROR: Failed to create socket.\n");
		exit(1);
	}

	my_str("Welcome to the simple socket client!\n");
	my_str("------------------------------------\n\n");

	if ((shost = gethostbyname(argv[1])) == NULL) {
		my_str("\nERROR: Unable to resolve host.\n");
		close(fd);
		exit(1);
	}

	if (shost->h_length <= 0) {
		my_str("\nERROR: Failed to retrieve address for host.\n");
		close(fd);
		exit(1);
	}

	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(my_atoi(argv[2]));
	memcpy(&(saddr.sin_addr.s_addr), shost->h_addr, shost->h_length);

	if (connect(fd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
		my_str("\nERROR: Failed to connect to host.\n");
		close(fd);
		exit(1);
	}

	buff = (char *)xmalloc(256);
	my_str("Choose username: ");
	if ((n = read(STDIN_FILENO, buff, 256)) <= 0) {
		my_str("\nERROR: Username could not be read.\n");
		close(fd);
		exit(1);
	}
	username = my_strdup(buff);
	buff = my_strcpy("/nick ", buff);
	buff = my_strcat(buff, username);
	username[my_strlen(username) - 1] = '\0';
	my_char('\n');

	if (write(fd, buff, 256) < 0) {
		my_str("ERROR: Could not send username to host.\n");
		close(fd);
		exit(1);
	}

	if ((n = read(fd, buff, 256)) <= 0) {
		my_str("ERROR: Server failed to send acknowledgment.\n");
		close(fd);
		exit(1);
	}

	for (;;) {
		memset(buff, 0, 256);
		my_str(username);
		my_str(": ");
		if ((n = read(STDIN_FILENO, buff, 256)) == 0)
			continue;
		else if (n < 0) {
			my_str("\nERROR: Could not read from STDIN.\n");
			break;
		}

		if (write(fd, buff, 256) < 0) {
			my_str("\nERROR: Could not send message to host.\n");
			break;
		}

		args = my_str2vect(buff);
		if (my_strcmp("/exit", args[0]) == 0) {
			my_str("\nERROR: Client instance closed.\n");
			break;
		} else if (my_strcmp("/nick", args[0]) == 0) {
			free(username);
			username = my_strdup(&buff[6]);
			username[my_strlen(&buff[6]) - 1] = '\0';
		}
		free(args);

		alarm(5);
		if ((n = read(fd, buff, 256)) > 0)
			alarm(0);
		else if (n == 0) {
			my_str("\nERROR: Server failed to send acknowledgment.\n");
			break;
		}

	}

	close(fd);
	free(buff);
	free(username);

	return (0);
}
