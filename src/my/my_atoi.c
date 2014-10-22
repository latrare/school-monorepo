#include "my.h"

int
my_atoi(char *s)
{
    int n;
    short int i;

    for (n = 0, i = 1; *s != '\0'; s++) {
        i = (*s == '-') ? (i * -1) : (i);
		if (*s < '0' || *s > '9') {
			if (n == 0) {
				if ((*s == '-' || *s == '+') && ((*(s + 1) < '0' ||
					*(s + 1) > '9') && (*(s + 1) != '-' && *(s + 1) != '+')))
					break;
				else if (*s == ' ' || *s == '-' || *s == '+')
					continue;
			}
			break;
		} else
            n = (n > 0) ? (n * 10 + (*s - '0')) : (n + (*s - '0'));
    }

    return ((n > 0) ? (n * i) : (n));
}
