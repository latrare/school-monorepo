PROJECTS = mylist my
BASE = ..
INC = $(BASE)/include
CFLAGS = -Wall -Wextra -ggdb
RM = rm -fv

all:
	cc $(CFLAGS) -I$(INC) -o my_test -L$(BASE)/lib my_test.c -lmy
	cc $(CFLAGS) -I$(INC) -o mylist_test -L$(BASE)/lib mylist_test.c -lmylist -lmy

clean:
	for f in `find $(BASE) -name '$(PROJECT)_*.o'`; do $(RM) $$f; done
	for f in `find $(BASE) -name '.$(PROJECT)_*.sw*'`; do $(RM) $$f; done

fclean: clean
	$(RM) mylist_test
	$(RM) my_test

re: fclean all
