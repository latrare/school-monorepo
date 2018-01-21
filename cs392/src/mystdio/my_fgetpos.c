#include "mystdio.h"

int
my_fgetpos(t_my_file *fp, fpos_t *pos)
{
	int res;

	if ((res = my_ftell(fp)) >= 0)
		*pos = res;

	return ((res >= 0) ? 0 : -1);
}
