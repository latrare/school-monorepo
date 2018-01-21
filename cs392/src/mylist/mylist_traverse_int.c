#include "mylist.h"

/*
 * pre: takes head
 * post: traverses list, printing ints of nodes
 */
void
traverse_int(t_node *h)
{
	if (h != NULL) {
		for (; h != NULL; h = h->next) {
			if (h->elem != NULL)
				my_int(*(int *)h->elem);
			else
				my_str("NULL");
			my_char(' ');
		}
	}
}
