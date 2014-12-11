#include "mystdio.h"

int
my_fgetpos(t_my_file *fp, fpos_t *pos)
{
	if (fp != NULL) {
		*pos = fp->pos;
		return (0);
	}

	return (-1);
}
