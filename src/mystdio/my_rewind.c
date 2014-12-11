#include "mystdio.h"


void
my_rewind(t_my_file *fp)
{
	(void)my_fseek(fp, 0, SEEK_SET);
}
