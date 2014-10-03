PROJECT = mylist
NAME = lib$(PROJECT)
BASE = ../..
SRC = mylist_add_elem.c mylist_add_node.c mylist_add_node_at.c mylist_append.c mylist_count_nodes.c mylist_elem_at.c mylist_empty_list.c mylist_new_node.c mylist_node_at.c mylist_remove_last.c mylist_remove_node.c mylist_remove_node_at.c mylist_traverse_char.c mylist_traverse_int.c mylist_traverse_string.c
OBJ = $(SRC:.c=.o)
INC = $(BASE)/include
CFLAGS = -Wall -Wextra -ggdb
RM = rm -fv

all:
	cc $(CFLAGS) -I$(INC) -c $(SRC)
	ld -r $(OBJ) -o $(NAME).o
	ar rcs $(NAME).a $(NAME).o
	mv lib$(PROJECT).a $(BASE)/lib

clean:
	$(RM) $(NAME).o
	for f in `find $(BASE) -name '$(PROJECT)_*.o'`; do $(RM) $$f; done
	for f in `find $(BASE) -name '.$(PROJECT)_*.sw*'`; do $(RM) $$f; done

fclean: clean
	$(RM) $(BASE)/lib/$(NAME).a

re: fclean all
