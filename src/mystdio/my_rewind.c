#include "mystdio.h"


void
my_rewind(t_my_file *fp)
{
		if (fp != NULL) {
				(void)lseek(fp->fd, 0, SEEK_SET);
				fp->pos = 0;
		}
}
