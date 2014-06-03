#ifndef __LOG_H
#define __LOG_H
#define _BSD_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define WRITE O_CREAT | O_WRONLY | O_APPEND
#define READ O_RDONLY 


void exit_message(char *msg);

int open_log(unsigned short ID, int OPEN);

void write_log(int fd, char *msg);

void read_log(int fd);

void close_log(int fd);

#endif 