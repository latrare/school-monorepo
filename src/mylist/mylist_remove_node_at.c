#include "mylist.h"

/*
 * pre: takes head and offset from head
 * post: removes node at offset from head and returns element of node
 */
void *
remove_node_at(t_node **h, unsigned int n)
{
	void *e;
	t_node *tmp, *prev, *swp;
	
	if (h != NULL && *h != NULL) {
		if (n > 0) {
			for (tmp = (*h)->next, prev = *h; n > 1 && tmp->next != NULL; tmp = tmp->next, prev = prev->next, n--)
				;
			e = tmp->elem;
			swp = tmp;
			tmp = tmp->next;
			prev->next = tmp;
			free(swp);
	
			return (e);
		} else
			return (remove_node(h));
	} else
		return (NULL);
}
