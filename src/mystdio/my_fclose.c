#include "mystdio.h"

int
my_fclose(t_my_file *fp)
{
	if (fp != NULL)
		(void)my_fflush(fp);
		if (close(fp->fd) == 0)
			return (0);

	return (EOF);
}
