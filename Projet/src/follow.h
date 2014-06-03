#ifndef _FOLLOW_H
#define _FOLLOW_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct fol{
	unsigned short ID;
	struct fol *next;
}Follow;


void error_message(char *msg);

Follow* allocate_follow(unsigned short ID);

void free_all_follow(Follow **follow);

void free_a_follow(Follow **follow, unsigned short ID);

int search_follow(Follow *follow, unsigned short ID);

void insert_follow(Follow **follow, Follow *fol);

void print_follow(Follow *follow);

int add_follow(Follow **follow, unsigned short ID);

#endif