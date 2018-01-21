#include "mylist.h"

/*
 * pre: takes head
 * post: frees entire list'
 */
void
empty_list(t_node **h)
{
	if (h != NULL && *h != NULL)
		while ((*h) != NULL)
			remove_node(h);
}
