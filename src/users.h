#ifndef __USERS_H
#define __USERS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "follow.h"

#define SIZE_BUFFER 145
#define MAX_USERS 30
#define USERS_MAX(x) (x>=MAX_USERS)?TRUE:FALSE

typedef struct{
	unsigned short ID;
	char *login;
	Follow *following;
} Users;

Users connected[MAX_USERS];
unsigned char numberOfUsers;

int truncate_string(char *msg);

void init_users();

void swap_user(Users *first, Users *second);

int create_user(unsigned short ID, char *login);

int search_user(unsigned short ID);

void print_user(Users user, unsigned short ID);

void print_all_user( unsigned short ID);

void delete_user(unsigned short ID);

void delete_all_users();

#endif 
