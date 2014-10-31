#define _H_SERVER_

#include "sockets.h"

/*
 * The server.
 * ---
 * Receives connections from clients. Forks into child process for each client.
 * Clients send text to server, server prints out text attached to handle.
 * Server interprets and alters output based on commands.
 */
int
main(int argc, char **argv)
{
	int port, pid, n, i;
	char *buff, *username, **args;
	struct sockaddr_in saddr, caddr;
	socklen_t clen;

	if (argc != 2 || (port = my_atoi(argv[1])) < 1 || port > (2 << 15) - 1) {
		my_str("usage: ./server SERVER_PORT\n");
		exit(1);
	}

	signal(SIGINT, sv_bye);

	my_str("Welcome to the simple socket server!\n");
	my_str("------------------------------------\n\n");

	if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		my_str("ERROR: Failed to create socket.\n");
		exit(1);
	}

	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
		my_str("ERROR: Failed to bind to socket.\n");
		close(sfd);
		exit(1);
	}

	if (listen(sfd, 5) < 0) {
		my_str("ERROR: Failed to listen on socket.\n");
		close(sfd);
		exit(1);
	}

	for (clen = sizeof(caddr);;) {
		memset(&caddr, 0, sizeof(caddr));
		if ((cfd = accept(sfd, (struct sockaddr *)&caddr, &clen)) < 0) {
			my_str("\nERROR: Failed to accept on socket.\n");
			break;
		}

		if ((pid = fork()) < 0) {
			my_str("\nERROR: Process could not fork.\n");
			close(cfd);
			close(sfd);
			exit(1);
		} else if (pid > 0) {
			/* parent */
			continue;
		} else {
			/* child */
			signal(SIGINT, sv_cbye);
			for (buff = (char *)xmalloc(256), i = 0; (n = read(cfd, buff, 256)) > 0;) {
				args = my_str2vect(buff);
				if (my_strcmp("/exit", args[0]) == 0) {
					if (i > 0) {
						my_str("***");
						my_str(username);
						my_str(" disconnected.\n");
					}
					break;
				} else if (my_strcmp("/nick", args[0]) == 0) {
					my_str("***");
					if (i > 0) {
						my_str(username);
						my_str(" changed name to ");
						free(username);
						username = my_strdup(my_strfind(buff, '/') + 6);
						username[my_strlen(username) - 1] = '\0';
						my_str(username);
						my_char('\n');
					} else {
						i++;
						username = my_strdup(my_strfind(buff, '/') + 6);
						username[my_strlen(username) - 1] = '\0';
						my_str(username);
						my_str(" connected.\n");
					}
				} else if (my_strcmp("/me", args[0]) == 0) {
					my_str("***");
					my_str(username);
					my_str(" ");
					my_str(my_strfind(buff, '/') + 4);
				} else {
					my_str(username);
					my_str(": ");
					my_str(buff);
				}

				/* Acknowledge client */
				if ((n = write(cfd, ".", 2)) < 0) {
					my_str("\nERROR: Failed to send ACK to ");
					my_str(username);
					my_char('\n');
					break;
				}

				my_freevect(args);
				args = NULL;
			}

			close(sfd);
			close(cfd);
			free(buff);
			if (i > 0)
				free(username);
			my_freevect(args);
			exit(0);
		}
	}

	close(sfd);

	return (0);
}
