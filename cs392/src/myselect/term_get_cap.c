#include "myselect.h"

/*
 * pre:
 * post:
 */
char *
term_get_cap(char* s)
{
	char *ret;
	static char area[2048];

	if (!(ret = tgetstr(s, (char **)&area))) {
		my_str("ERROR: Cap: ");
		my_str(s);
		my_str(" not found!\n");
		restore_terminal();
		exit(1);
	}

	return (ret);
}
