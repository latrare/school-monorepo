PROJECT = my
NAME = lib$(PROJECT)stdio
BASE = ../..
INC = INC = $(BASE)/include
LIB = $(BASE)/lib
SRC = my_fopen.c my_fclose.c my_fgetc.c my_fgets.c my_fflush.c my_fputc.c my_fputs.c my_fseek.c my_rewind.c my_ftell.c my_fgetpos.c my_fsetpos.c my_fread.c my_fwrite.c
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
