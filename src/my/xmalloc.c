#include "my.h"

/*
 * pre: takes unsigned int size to be allocated
 * post: returns pointer to newly assigned memory or NULL
 */
void *
xmalloc(unsigned int n)
{
	void *p;

	p = NULL;
	if ((p = malloc(n)) == NULL) {
		my_str("\nVirtual memory exhausted.\n");
		exit(1);
	}

	return (p);
}
