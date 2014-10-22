/*
 * Trevor Miranda
 *
 * Project Description:
 * ---
 * Create a client that sends a server of a specific PID a message.
 */
#include "my.h"

#ifndef _H_SERVER_
#define _H_SERVER_
#include <signal.h>
typedef struct s_gl_env {
	int ack  : 1;
	int done : 1;
	pid_t clpid;
} t_gl_env;
t_gl_env gl_env;

void getclpid(int);
void getclchar(int);
#endif

#ifndef _H_CLIENT_
#define _H_CLIENT_
#include <signal.h>
void ack(int);
void putclchar(char, pid_t);
void putclpid(pid_t, pid_t);

int gl_env_ack;
#endif

#if defined(_H_SERVER_) || defined(_H_CLIENT_)
void bye(int);
#endif
