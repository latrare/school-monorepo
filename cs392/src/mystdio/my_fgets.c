#include "mystdio.h"

char *
my_fgets(char *s, int size, t_my_file *fp)
{
	int size_real;

	if (fp != NULL && s != NULL && (fp->flag & O_WRONLY) == 0) {
		if ((size_real = read(fp->fd, s, size)) >= 0) {
			fp->pos += size_real;
			s[size_real] = '\0';
			return (s);
		}
	}

	return (NULL);
}
