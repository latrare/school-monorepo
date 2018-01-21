#include "mylist.h"

/*
 * pre: takes head
 * post: removes element at tail-end of list and returns element of that node
 */
void *
remove_last(t_node **h)
{
	void *e;
	t_node *post, *tmp;

	e = NULL;
	if (h != NULL && *h != NULL) {
		if ((*h)->next != NULL) {
			for (tmp = *h; tmp->next->next != NULL; tmp = tmp->next)
				;
			post = tmp->next;
			e = post->elem;
			tmp->next = NULL;
			free(post);
		} else {
			e = (*h)->elem;
			free(*h);
		}
	}

	return (e);
}
