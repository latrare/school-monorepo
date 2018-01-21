#include "mystdio.h"


long int
my_ftell(t_my_file *fp)
{
		if (fp != NULL)
				return (fp->pos);

		return (-1);
}
