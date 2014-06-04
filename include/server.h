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
#include "log.h"
#include "users.h"

#define BUFSIZE 1024

struct sockaddr_in init_socket(int port) ;

int create_socket(int port);



#endif /* __SERVER_H */
