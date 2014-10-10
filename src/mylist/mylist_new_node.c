#include "mylist.h"

/*
 * pre: takes elem and next node pointer
 * post: creates and returns new node with given element and next node pointer
 */
t_node *
new_node(void *e, t_node *n)
{
	t_node *tmp;

	tmp = NULL;
	if (e != NULL) {
		tmp = (t_node *)xmalloc(sizeof(t_node));
		tmp->elem = e;
		tmp->next = n;
	}

	return (tmp);
}
