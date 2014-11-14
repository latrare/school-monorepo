#include "myselect.h"

/*
 * pre:
 * post:
 */
void
show_elems()
{
	int i, x, y, w;

	ioctl(0, TIOCGWINSZ, &gl_env.win);
	gl_env.lpos = gl_env.pos;
	gl_env.flag = 0;
	term_clear();

	for (i = 0, x = 0, y = 0, w = 0; i < gl_env.nbelems; i++, y++) {
		if (y >= gl_env.win.ws_row) {
			x += w + 4;
			y = 0;
			w = 0;
		}
		if (w < gl_env.elements[i].size)
			w = gl_env.elements[i].size;
		if (x + w >= gl_env.win.ws_col) {
			term_clear();
			my_str("Please make window larger.\n");
			gl_env.flag = 1;
			break;
		}
		gl_env.elements[i].x = x;
		gl_env.elements[i].y = y;
		refreshout(i);
	}

	term_move_to_item(gl_env.lpos);
	refreshin();
}
