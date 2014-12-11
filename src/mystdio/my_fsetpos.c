#include "mystdio.h"

int
my_fsetpos(t_my_file *fp, fpos_t *pos)
{
	if (fp != NULL) {
		fp->pos = *pos;
		if (lseek(fp->fd, *pos, SEEK_SET) == *pos)
			return (0);
	}

	return (-1);
}
