NAME = mypipes
BASE = ../..
SRC = pipes.c
OBJ = pipes.o
INC = $(BASE)/include
LIB = $(BASE)/lib
CFLAGS = -Wall -Wextra -ggdb
RM = rm -fv

all:
	cc $(CFLAGS) -I$(INC) -L$(LIB) $(SRC) -lmy -o $(SRC:.c=)

clean:
	$(RM) $(OBJ)
	$(RM) .*_*.sw*

fclean: clean
	$(RM) $(SRC:.c=)

re: clean all
