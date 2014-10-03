#include "mylist.h"

/*
 * pre: takes head
 * post: traverses list, printing chars
 */
void
traverse_char(t_node *h)
{
	if (h != NULL) {
		for (; h != NULL; h = h->next) {
			if (h->elem != NULL)
				my_char(*(char *)h->elem);
			else
				my_str("NULL");
			my_char(' ');
		}
	}
}
