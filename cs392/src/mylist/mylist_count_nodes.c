#include "mylist.h"

/*
 * pre: takes head
 * post: returns count of nodes from head to end
 */
unsigned int
count_nodes(t_node *h)
{
	int i;

	i = 0;
	if (h != NULL)
		for (; h != NULL; i++, h = h->next)
			;

	return (i);
}
