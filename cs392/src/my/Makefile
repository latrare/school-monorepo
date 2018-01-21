PROJECT = my
NAME = lib$(PROJECT)
BASE = ../..
INC = $(BASE)/include
LIB = $(BASE)/lib
SRC = my_alpha.c my_char.c my_digits.c my_int.c my_num_base.c my_revstr.c my_str.c my_strcat.c my_strcmp.c my_strconcat.c my_strcpy.c my_strdup.c my_strfind.c my_strlen.c my_strncmp.c my_strnconcat.c my_strncpy.c my_strpos.c my_strrfind.c my_strrpos.c my_vect2str.c my_str2vect.c my_freevect.c my_atoi.c xmalloc.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -ggdb
RM = rm -fv

all:
	cc $(CFLAGS) -I$(INC) -c $(SRC)
	ld -r $(OBJ) -o $(NAME).o
	ar rcs $(NAME).a $(NAME).o
	mv $(NAME).a $(LIB)

clean:
	$(RM) $(OBJ)
	$(RM) $(NAME).o

fclean: clean
	$(RM) $(LIB)/$(NAME).a

re: fclean all
