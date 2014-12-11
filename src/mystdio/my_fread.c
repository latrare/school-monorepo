#include "mystdio.h"

size_t
my_fread(void *ptr, size_t size, size_t nmemb, t_my_file *fp)
{
	int c;
	size_t s, total;

	if (ptr != NULL && fp != NULL && (fp->flag & O_WRONLY) == 0) {
		for (total = 0; total < nmemb * size; total += size) {
			for (s = 0; s < size; s++) {
				if ((c = my_fgetc(fp)) != EOF)
					((char *)ptr)[total + s] = (char)c;
			}
		}

		/* XXX: I don't think this is the right thing to return. */
		return (nmemb);
	}

	return (0);
}
