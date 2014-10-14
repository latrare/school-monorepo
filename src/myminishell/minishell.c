#include "my.h"

int
main()
{
	int i, pid;
	char buff[256];
	char **v;

	for (i = 0; i < 256; i++)
		buff[i] = 0;

	for (;;) {
		my_str("minish #> ");
		if (read(STDIN_FILENO, buff, 256) < 0) {
			my_str("Internal error when reading input.\n");
			exit(1);
		}
		if ((v = my_str2vect(buff)) == NULL) {
			my_str("Internal error when converting input to vector.\n");
			exit(1);
		}
		if (my_strcmp(v[0], "cd") == 0) {
			if (chdir(v[1]) < 0)
				my_str("Failed to change working directory.\n");
			continue;
		}
		if (my_strcmp(v[0], "exit") == 0) {
			my_str("So long and thanks for all the fish!\n");
			exit(1);
		}
		if ((pid = fork()) < 0) {
			my_str("Failed to fork to execute command.\n");
			exit(1);
		}
		if (pid > 0) {
			wait();
			free(v);
		} else {
			if (execvp(v[0], v) < 0)
				my_str("Invalid command entered.\n");
			exit(0);
		}
	}

	return (0);
}
