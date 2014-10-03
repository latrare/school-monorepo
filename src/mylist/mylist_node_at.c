#include "mylist.h"

/*
 * pre: takes head node and offset to find node from head
 * post: returns pointer to node at offset from head
 */
t_node *
node_at(t_node* h, unsigned int n)
{
	if (h != NULL) {
		for (; h->next != NULL && n > 0; h = h->next, n--)
			;
		
		return (h);
	} else
		return (NULL);	
}
