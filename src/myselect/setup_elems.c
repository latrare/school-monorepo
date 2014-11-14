#include "myselect.h"

/*
 * pre:
 * post:
 */
void
setup_elems(int argc, char **argv)
{
	int i;

	gl_env.nbelems = argc;
	gl_env.elements = xmalloc(gl_env.nbelems * sizeof(t_elem));
	for (i = 0; i < gl_env.nbelems; i++) {
		gl_env.elements[i].elem = argv[i];
		gl_env.elements[i].size = my_strlen(argv[i]);
		gl_env.elements[i].x = 0;
		gl_env.elements[i].y = 0;
		gl_env.elements[i].mode = 0;
	}
}
