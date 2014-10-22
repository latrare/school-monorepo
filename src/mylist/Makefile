PROJECT = mylist
NAME = lib$(PROJECT)
BASE = ../..
INC = $(BASE)/include
LIB = $(BASE)/lib
SRC = mylist_add_elem.c mylist_add_node.c mylist_add_node_at.c mylist_append.c mylist_count_nodes.c mylist_elem_at.c mylist_empty_list.c mylist_new_node.c mylist_node_at.c mylist_remove_last.c mylist_remove_node.c mylist_remove_node_at.c mylist_traverse_char.c mylist_traverse_int.c mylist_traverse_string.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -ggdb
RM = rm -fv

all:
	cc $(CFLAGS) -I$(INC) -c $(SRC)
	ld -r $(OBJ) -o $(NAME).o
	ar rcs $(NAME).a $(NAME).o
	mv $(NAME).a $(LIB)

clean:
	$(RM) $(OBJS)
	$(RM) $(NAME).o

fclean: clean
	$(RM) $(LIB)/$(NAME).a

re: fclean all
