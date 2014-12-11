#include "mystdio.h"

t_my_file *
my_fopen(char *name, char *mode)
{
	int fd, flags;
	long cur, end;
	short i, b, m, p;
	t_my_file *newfp;

	newfp = NULL;
	if (name != NULL && mode != NULL) {
		for (i = 0, b = 0, m = 0, p = 0, flags = 0; mode[i] != '\0'; i++) {
			if (i > 2)
				return (NULL);
			if (mode[i] == 'b') {
				if (b == 0)
					b = 1;
				else
					return (NULL);
			}
			if (mode[i] == READWRITE) {
				if (p == 0 && m == 1) {
					p = 1;
					if ((flags & O_WRONLY) > 0)
						flags |= O_CREAT;
					flags = (flags & ~O_WRONLY) | O_RDWR;
				} else
					return (NULL);
			}
			if ((mode[i] == READ || mode[i] == WRITE || mode[i] == APPEND) && m == 0) {
				m = 1;
				if (mode[i] == READ)
					flags |= O_RDONLY;
				else if (mode[i] == WRITE)
					flags |= O_WRONLY | O_TRUNC;
				else if (mode[i] == APPEND)
					flags |= O_WRONLY | O_APPEND | O_CREAT;
			}
		}

		if ((fd = open(name, flags)) > 0) {
			cur = lseek(fd, 0, SEEK_CUR);
			end = lseek(fd, 0, SEEK_END);
			if ((flags & O_APPEND) == 0)
				lseek(fd, cur, SEEK_SET);
			newfp = (t_my_file *)xmalloc(sizeof(t_my_file *));
			newfp->fd = fd;
			newfp->buff = (char *)xmalloc(BUFF_SIZE);
			for (i = 0; i < BUFF_SIZE; i++)
				newfp->buff[i] = '\0';
			newfp->pos = ((flags & O_APPEND) > 0) ? end : cur;
			newfp->posw = 0;
			newfp->taille = end;
			newfp->flag = flags;
		}
	}

	return (newfp);
}
