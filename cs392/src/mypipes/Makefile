PROJECT = my
NAME = pipes
BASE = ../..
INC = $(BASE)/include
LIB = $(BASE)/lib
SRC = pipes.c
OBJ = pipes.o
CFLAGS = -Wall -Wextra -ggdb
RM = rm -fv

all:
	cc $(CFLAGS) -I$(INC) -L$(LIB) $(SRC) -l$(PROJECT) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: clean all
