PROJECT = my
NAME = select
BASE = ../..
INC = $(BASE)/include
LIB = $(BASE)/lib
SRC = check_char.c doselect.c  getout.c init_caps.c init_terminal.c main.c movedown.c moveleft.c moveright.c moveup.c my_termprint.c refreshin.c refreshout.c restore_terminal.c setup_elems.c show_elems.c term_clear.c term_get_cap.c term_move.c term_move_to_item.c term_standend.c term_standout.c term_underend.c term_underline.c term_ve.c term_vi.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -ggdb
RM = rm -fv

all:
	cc $(CFLAGS) -I$(INC) -L$(LIB) $(SRC) -ltermcap -lmy -o $(PROJECT)$(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(PROJECT)$(NAME)

re: fclean all
