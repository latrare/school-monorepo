#include "myselect.h"

/*-
 * Trevor Miranda
 *
 * Project Description
 * ---
 *  Simple selection menu written using termcaps.
 *
 */
int
main(int argc, char **argv)
{
	int n;
	char buff[READMIN + 5];

	if (argc <= 1 || argv == NULL) {
		my_str("usage: ./myselect LIST_OF_SPACE_DELIMITED_INPUTS\n");
		exit(1);
	}

	signal(SIGWINCH, show_elems);
	init_caps();
	init_terminal();
	setup_elems(argc - 1, &argv[1]);
	term_vi();
	show_elems();

	for (;;) {
		n = read(0, &buff, READMIN + 5);
		buff[n] = '\0';
		check_char(buff);
	}

	return (0);
}
