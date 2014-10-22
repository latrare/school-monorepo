NAME = mysignals
BASE = ../..
SRC = ack.c bye.c getclchar.c getclpid.c putclchar.c putclpid.c
CLSRC = client.c
SVSRC = server.c
OBJ = $(SRC:.c=.o)
INC = $(BASE)/include
LIB = $(BASE)/lib
CFGLAGS = -Wall -Wextra -ggdb
RM = rm -fv

re: fclean all

all: client server

client:
	gcc $(CFLAGS) -I$(BASE)/include -L$(BASE)/lib $(SRC) $(CLSRC) -lmy -o $(CLSRC:.c=)

server:
	gcc $(CFLAGS) -I$(BASE)/include -L$(BASE)/lib $(SRC) $(SVSRC) -lmy -o $(SVSRC:.c=)

clean:
	$(RM) $(OBJ)
	$(RM) $(CLSRC:.c=.o)
	$(RM) $(SVSRC:.c=.o)

fclean: clean
	$(RM) $(CLSRC:.c=)
	$(RM) $(SVSRC:.c=)
