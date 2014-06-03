#ifndef __USERS_H
#define __USERS_H

#include <stdio.h>
#include <stdlib.h>
#include "follow.h"

#define MAX_USERS 30
#define SIZE_MAX(x) (x>=MAX_USERS)?TRUE:FALSE

typedef struct{
	unsigned short ID;
	char *login;
	Follow *following;
}Users;

Users connected[MAX_USERS];
unsigned char numberOfUsers;

void init_users();

void swap_user(Users *first, Users *second);

int create_user(unsigned short ID, char *login);

int search_user(unsigned short ID);

void print_user(Users user);

void print_all_user();

void delete_user(unsigned short ID);

void delete_all_users();

#endif 
