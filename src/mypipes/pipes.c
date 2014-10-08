/*-
 * Trevor Miranda
 * 
 * Project Description
 * ---
 * Demonstration of piping and forking to send along message through two children processes.
 */
#include "my.h"

int
main(int argc, char **argv)
{
	int pid, n;
	int fd[2];
	char *outbuff, *inbuff;
	
	if (argc < 2) {
		my_str("Usage: ./pipes STRING TO SEND HERE\n");
		exit(1);
	}
	pipe(fd);
	if ((pid = fork()) < 0) {
		my_str("Process could not fork!\n");
		exit(1);
	} else if (pid > 0) {
		/* Grandpa */
		close(fd[0]);
		outbuff = my_vect2str(&argv[1]);
		my_str("Grandpa sending: '");
		my_str(outbuff);
		my_str("'\n");
		write(fd[1], outbuff, my_strlen(outbuff) + 1);
		free(outbuff);
	} else {
		/* Dad */
		inbuff = (char *)xmalloc(1000);
		n = read(fd[0], inbuff, 1000);
		if (n > 0) {
			my_str("Dad receiving: '");
			my_str(inbuff);
			my_str("'\n");
			if ((pid = fork()) < 0) {
				my_str("Child process could not fork!\n");
				exit(1);
			} else if (pid > 0) {
				write(fd[1], inbuff, 1000);
				free(inbuff);
			} else {
				/* Child */
				n = read(fd[0], inbuff, 1000);
				if (n > 0) {
					my_str("Child receiving: '");
					my_str(inbuff);
					my_str("'\n");
					exit(0);
				} else
					exit(1);
			}
			exit(0);
		} else
			exit(1);
	}

	return (0);
}
