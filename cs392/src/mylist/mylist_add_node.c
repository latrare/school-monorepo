#include "mylist.h"

/*
 * pre: takes node and head
 * post: places given node at head
 */
void
add_node(t_node *n, t_node **h)
{
	if (n != NULL) {
		if (h != NULL && *h != NULL) {
			n->next = *h;
			*h = n;
		} else if (h != NULL && *h == NULL)
			*h = n;
	}
}
