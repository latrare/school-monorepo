#include "mystdio.h"

size_t
my_fwrite(void *ptr, size_t size, size_t nmemb, t_my_file *fp)
{
	size_t s, total;

	if (ptr != NULL) {
		for (total = 0; total < nmemb * size; total += size) {
			for (s = 0; s < size; s++) {
				if (my_fputc(((char *)ptr)[total + s], fp) != ((char *)ptr)[total + s])
					return (0);
			}
		}

		/* XXX: I don't think this is the right thing to return. */
		return (nmemb);
	}

	return (0);
}
