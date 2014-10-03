#include "mylist.h"

/*
 * pre: takes head
 * post: returns count of nodes from head to end
 */
unsigned int
count_nodes(t_node *h)
{
	int i;

	if (h != NULL) {
		for (i = 0; h != NULL; i++, h = h->next)
			;
		return (i);
	} else
		return (0);
}
