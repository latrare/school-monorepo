#include "mystdio.h"


int
my_fseek(t_my_file *fp, long off, int seek)
{
	long pos;

	if (fp != NULL) {
		if (seek == SEEK_SET || seek == SEEK_CUR || seek == SEEK_END) {
			if ((pos = lseek(fp->fd, off, seek)) != -1) {
				fp->pos = pos;
				return (0);
			}
		}
	}

	return (-1);
}
