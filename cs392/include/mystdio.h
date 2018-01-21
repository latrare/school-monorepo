/*
** my_stdio.h for libstream in
**
** Made by steven gabarro
** Login <xxxxxxxx@epita.fr>
**
** Started on Sat Nov 27 01:04:56 1999 steven gabarro
** Last update Wed Dec 1 05:14:19 1999 steven gabarro
*/

#ifndef __MY_STDIO_H__
#define __MY_STDIO_H__

#include <fcntl.h>
#include <unistd.h>

#include "my.h"

# define BUFF_SIZE 4096
# define READ 'r'
# define WRITE 'w'
# define APPEND 'a'
# define READWRITE '+'

# ifndef EOF
# define EOF (-1)
# endif

# ifndef fpos_t
typedef long fpos_t;
# endif

# ifndef SEEK_SET
# define SEEK_SET 0
# endif
# ifndef SEEK_CUR
# define SEEK_CUR 1
# endif
# ifndef SEEK_END
# define SEEK_END 2
# endif

typedef struct s_my_file {
	int fd;
	char *buff;
	int pos;
	int posw;
	int taille;
	int flag;
} t_my_file;

t_my_file *my_fopen(char *, char *);
int       my_fclose(t_my_file *);
int       my_fgetc(t_my_file *);
char      *my_fgets(char *, int, t_my_file *);
int       my_fflush(t_my_file *);
int       my_fputc(int, t_my_file *);
int       my_fputs(char *, t_my_file *);
int       my_fseek(t_my_file *, long, int);
void      my_rewind(t_my_file *);
long      my_ftell(t_my_file *);
int       my_fgetpos(t_my_file *, fpos_t *);
int       my_fsetpos(t_my_file *, fpos_t *);
size_t    my_fread(void *, size_t, size_t, t_my_file *);
size_t    my_fwrite(void *, size_t, size_t, t_my_file *);

#endif
