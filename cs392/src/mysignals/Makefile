PROJECT = my
NAME = signals
BASE = ../..
INC = $(BASE)/include
LIB = $(BASE)/lib
SRC = ack.c bye.c getclchar.c getclpid.c putclchar.c putclpid.c
CLSRC = client.c
SVSRC = server.c
OBJ = $(SRC:.c=.o)
CFGLAGS = -Wall -Wextra -ggdb
RM = rm -fv

all: client server

client:
	cc $(CFLAGS) -I$(INC) -L$(LIB) $(SRC) $(CLSRC) -l$(PROJECT) -o $(CLSRC:.c=)

server:
	cc $(CFLAGS) -I$(INC) -L$(LIB) $(SRC) $(SVSRC) -l$(PROJECT) -o $(SVSRC:.c=)

clean:
	$(RM) $(OBJ)
	$(RM) $(CLSRC:.c=.o)
	$(RM) $(SVSRC:.c=.o)

fclean: clean
	$(RM) $(CLSRC:.c=)
	$(RM) $(SVSRC:.c=)

re: fclean all
