#include <stdlib.h>

#include "my.h"

void *
xmalloc(unsigned int n)
{
	void *p;

	if ((p = malloc(n)) == NULL) {
		my_str("\nVirtual memory exhausted.\n");
		exit(1);
	}

	return (p);
}
