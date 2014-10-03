/*-
 * Trevor Miranda
 *
 * Project Description:
 * A linked-list implementation.
 */
#ifndef _MYLIST_H_
#define _MYLIST_H_

#include "my.h"

typedef struct s_node {
	void 		  *elem;
	struct s_node *next;
} t_node;

t_node *new_node(void *, t_node *);

/*
 * Syntax: elem, head
 * add_node(elem, &head); -- How it will often be called
 */
void add_node(t_node *, t_node **);

void add_elem(void *, t_node **);

/* One parse. (Calling add_node in it would violate this.) */
void append(t_node *, t_node **);

/* One parse. */
void add_node_at(t_node *, t_node **, unsigned int);

/* Remove node at head. Return elem from node that is removed. */
void *remove_node(t_node **);

/* One parse. Remove node at index. Return elem. */
void *remove_node_at(t_node **, unsigned int);

/* One parse. */
void *remove_last(t_node **);

unsigned int count_nodes(t_node *);

/* Not longer than 2 lines */
void empty_list(t_node **);

t_node *node_at(t_node *, unsigned int);

void *elem_at(t_node *, unsigned int);

/* Prints all ints in list, whitespace-delimited */
void traverse_int(t_node *);

/* Prints all chars in list, whitespace-delimited */
void traverse_char(t_node *);

/* Prints all strings in list, whitespace-delimited */
void traverse_string(t_node *);

#endif
