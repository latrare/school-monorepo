#include "mystdio.h"

int
my_fgetc(t_my_file *fp)
{
	char c;
	char *buff;

	if (fp != NULL && (fp->flag & O_WRONLY) == 0) {
		if (fp->pos + 1 <= fp->taille) {
			fp->pos++;
			buff = (char *)xmalloc(1);
			if (read(fp->fd, buff, 1) == 1) {
				c = buff[0];
				free(buff);
				return ((int)c);
			}
		}
	}

	return (EOF);
}
