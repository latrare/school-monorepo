#include  "mylist.h"

/*
 * pre: takes generic elem and head
 * post: creates new node with elem and places it at head
 */
void
add_elem(void *e, t_node **h)
{
	t_node *n;
	
	n = new_node(e, NULL);
	if (n != NULL)
		add_node(n, h);
}
