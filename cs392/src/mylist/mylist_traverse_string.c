#include "mylist.h"

/*
 * pre: takes head
 * post: traverses list, printing strings in nodes
 */ 
void
traverse_string(t_node *h)
{
	if (h != NULL) {
		for (; h != NULL; h = h->next) {
			if (h->elem != NULL)
				my_str(*(char **)h->elem);
			else
				my_str("NULL");
			my_char(' ');
		}
	}
}
