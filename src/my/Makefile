PROJECT = my
NAME = lib$(PROJECT)
BASE = /home/tmiranda/Work/cs392
SRC = my_alpha.c my_char.c my_digits.c my_int.c my_num_base.c my_revstr.c my_str.c my_strcat.c my_strcmp.c my_strconcat.c my_strcpy.c my_strdup.c my_strfind.c my_strlen.c my_strncmp.c my_strnconcat.c my_strncpy.c my_strpos.c my_strrfind.c my_strrpos.c xmalloc.c
TEST = $(BASE)/test
OBJ = $(SRC:.c=.o)
INC = $(BASE)/include
CFLAGS = -Wall -Wextra -ggdb
RM = rm -fv

all: lib test

lib:
	cc $(CFLAGS) -I$(INC) $(SRC) -c $(SRC)
	ld -r $(OBJ) -o $(NAME).o
	ar rcs $(NAME).a $(NAME).o
	mv lib$(PROJECT).a $(BASE)/lib

test:
	cc $(CFLAGS) -I$(INC) -o $(TEST)/$(PROJECT)_test -L$(BASE)/lib $(TEST)/$(PROJECT)_test.c -l$(PROJECT)

clean:
	$(RM) $(NAME).o
	for f in `find $(BASE) -name '$(PROJECT)_*.o'`; do $(RM) $$f; done
	for f in `find $(BASE) -name '.$(PROJECT)_*.sw*'`; do $(RM) $$f; done

fclean: clean
	$(RM) $(BASE)/lib/$(NAME).a
	$(RM) $(TEST)/$(PROJECT)_test

re: fclean all
