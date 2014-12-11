#include "mystdio.h"

int
my_fputc(int c, t_my_file *fp)
{
	if (fp != NULL && fp->flag != O_RDONLY) {
		fp->buff[fp->posw] = c;
		fp->posw++;
		(void)my_fflush(fp);
		return (c);
	}

	return (EOF);
}
