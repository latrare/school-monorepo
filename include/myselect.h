#ifndef _MYSELECT_H_
#define _MYSELECT_H_

#include <sys/ioctl.h>
#include <sys/termios.h>

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <termcap.h>
#include <termios.h>
#include <unistd.h>

#include "my.h"

#define READTIME 1
/* used to return from read after 1/10th of  second passed from the first byte read */

#define READMIN 3
/* used to return from min if 3 bytes have been read. Needed for things like characters which are \E[A B C or D */

#ifndef NULL
#define NULL (0)
#endif

#define KU "\E[A"
#define KD "\E[B"
#define KR "\E[C"
#define KL "\E[D"
#define UP "ku"
#define DOWN "kd"
#define LEFT "kl"
#define RIGHT "kr"
#define CLEAR "cl"
#define MOVE "cm"
#define STANDOUT "so"
#define STAND_END "se"
#define UNDERLINE "us"
#define UNDER_END "ue"
#define CURSOROFF "vi"
#define CURSORON "ve"
#define VECAP "\E[?25h" // actual string for VE in case tgetstr doesn't find it
#define VICAP "\E[?25l" // same as above but for VI
#define ESC 27

typedef struct s_elem
{
	char *elem;
	int  size;
	int  x;
	int  y;
	int  mode;
} t_elem;

typedef struct s_env
{
	char           *left;
	char           *right;
	char           *up;
	char           *down;
	char           *esc;
	char           *underline;
	char           *under_end;
	char           *standout;
	char           *stand_end;
	char           *move;
	char           *clear;
	char           *cursoroff;
	char           *cursoron;
	struct winsize win;
	struct termio  line_backup;
	int            flag;
	int            stdio_backup;
	int            nbelems;
	int            pos;
	int            lpos;
	t_elem         *elements;
} t_env;

t_env gl_env;
// created as a structure to limit number of globals to 1

void init_terminal();
void restore_terminal();
char *term_get_cap(char*);
void init_caps();
int  my_termprint(int);
void term_clear();
void term_vi();
void term_ve();
void check_char(char *);
char get_win_size();
void show_elems();
void refreshin();
void refreshout(int);
void moveup();
void movedown();
void moveleft();
void moveright();
void doselect();
void getout(char);
void setup_elems(int, char**);
void term_move_to_item(int);
void term_underline();
void term_standout();
void term_standend();
void term_underend();
void term_move(int, int);

#endif
