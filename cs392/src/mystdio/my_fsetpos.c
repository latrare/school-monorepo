#include "mystdio.h"

int
my_fsetpos(t_my_file *fp, fpos_t *pos)
{
	return (my_fseek(fp, *pos, SEEK_SET));
}
