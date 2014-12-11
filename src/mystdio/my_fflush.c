#include "mystdio.h"

int
my_fflush(t_my_file *fp)
{
	int i;

	if (fp != NULL) {
		if ((fp->flag & O_APPEND) > 0)
			(void)my_fseek(fp, 0, SEEK_END);
		if (write(fp->fd, fp->buff, fp->posw) >= 0) {
			for (i = 0; i < fp->posw; i++)
				fp->buff[i] = '\0';
			if (fp->pos + fp->posw > fp->taille)
				fp->taille += fp->posw;
			fp->pos += fp->posw;
			fp->posw = 0;
			return (0);
		}
	}

	return (EOF);
}
