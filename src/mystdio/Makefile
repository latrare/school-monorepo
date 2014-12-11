SRC = my_fopen.c my_fclose.c my_fgetc.c my_fgets.c my_fflush.c my_fputc.c my_fputs.c my_fseek.c my_rewind.c my_ftell.c my_fgetpos.c my_fsetpos.c my_fread.c my_fwrite.c
OBJ = $(SRC:.c=.o)

all:
	cc -Wall -Wextra -ggdb -I../../include -c $(SRC)
	ld -r $(OBJ) -o libmystdio.o
	ar rcs libmystdio.a libmystdio.o
	mv libmystdio.a ../../lib

clean:
	rm *.o
