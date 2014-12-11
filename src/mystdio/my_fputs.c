#include "mystdio.h"

int
my_fputs(char *s, t_my_file *fp)
{
	if (fp != NULL && s != NULL && fp->flag != O_RDONLY) {
		for (; *s != '\0'; s++)
			if (fp->posw + 1 < BUFF_SIZE)
				fp->buff[fp->posw++] = *s;
		my_fflush(fp);
		return (0); /* Docs say to return a non-negative number */
	}

	return (EOF);
}
