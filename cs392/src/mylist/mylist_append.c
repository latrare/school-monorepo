#include "mylist.h"

/*
 * pre: takes node and head
 * post: places node at the tail-end of the list
 */
void
append(t_node *n, t_node **h)
{
	t_node *i;

	if (n != NULL) {
		if (h != NULL && *h != NULL) {
			for (i = *h; i->next != NULL; i = i->next)
				;
			i->next = n;
		} else
			(*h)->next = n;
	}
}
