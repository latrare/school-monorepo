#include "mystdio.h"

int
my_fflush(t_my_file *fp)
{
	int i, n;

	if (fp != NULL) {
		if ((n = write(fp->fd, fp->buff, fp->posw)) >= 0) {
			for (i = 0; i < fp->posw; i++)
				fp->buff[i] = '\0';
			if (fp->pos + n > fp->taille)
				fp->taille += n;
			if ((fp->flag & O_APPEND) > 0)
				(void)my_fseek(fp, 0, SEEK_END);
			fp->pos += n;
			fp->posw = 0;
			return (0);
		}
	}

	return (EOF);
}
