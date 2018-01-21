#include "mylist.h"

/*
 * pre: takes node, head, and offset from head
 * post: places node at offset from head
 */
void
add_node_at(t_node *t, t_node **h, unsigned int n)
{
	t_node *tmp;

	if (t != NULL) {
		if (h != NULL && *h != NULL) {
			if (n > 0) {
				for (tmp = *h; tmp->next != NULL && n > 1; tmp = tmp->next, n--)
					;
				t->next = tmp->next;
				tmp->next = t;
			} else
				add_node(t, h);
		} else
			*h = t;	
	}	
}
