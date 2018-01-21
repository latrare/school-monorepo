#include "mylist.h"

/*
 * pre: takes head and offset from head
 * post: returns element of node at offset from head
 */
void *
elem_at(t_node* h, unsigned int n)
{
	t_node *tmp;

	tmp = node_at(h, n);

	return (tmp != NULL ? tmp->elem : tmp);
}
