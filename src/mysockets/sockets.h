/*
 * Trevor Miranda
 *
 * Project Description
 * ---
 * Create client that can chat to server
 */
#include "my.h"

#ifndef _H_SOCKETS_
#define _H_SOCKETS_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <string.h>

#endif

/* Server portion */
#ifndef _H_CLIENT_
#define _H_CLIENT_

int sfd, cfd;

void sv_bye(int);
void sv_cbye(int);

#endif

/* Client portion */
#ifndef _H_SERVER_
#define _H_SERVER_

#include <netdb.h>

int fd;

void cl_bye(int);

#endif
