#include "mylist.h"

/*
 * pre: takes head
 * post: removes node at head and returns element at that node
 */
void *
remove_node(t_node **h)
{
	void *e;
	t_node *tmp;

	if (h != NULL && *h != NULL) {
		e = (*h)->elem;
		tmp = *h;
		*h = (*h)->next;
		free(tmp);

		return (e);
	} else
		return (NULL);
}
