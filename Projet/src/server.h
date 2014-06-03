#ifndef __SERVER_H
#define __SERVER_H

#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFSIZE 1024

int get_socket(unsigned short portnum);

void server_start(unsigned short portnum);

#endif /* __SERVER_H */
