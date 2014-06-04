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

/**
 * \fn void init_users()
 * \brief Permet d'initialiser la structure d'utilisateur.
 */
void init_users();

/**
 * \fn void swap_user(Users *first, Users *second)
 * \brief Echange dans la liste deux utilisateurs.
 */
void swap_user(Users *first, Users *second);

/**
 * \fn void swap_user(Users *first, Users *second)
 * \brief Créé un utilisateur.
 */
int create_user(unsigned short ID, char *login);

/**
 * \fn int search_user(unsigned short ID)
 * \brief Recherche un utilisateur existant.
 */
int search_user(unsigned short ID);

/**
 * \fn int search_user(unsigned short ID)
 * \brief Affiche un utilisateur en particulier.
 */
void print_user(Users user, unsigned short ID);

/**
 * \fn void print_all_user(unsigned short ID)
 * \brief Affiche tous les utilisateurs.
 */
void print_all_user( unsigned short ID);

/**
 * \fn void print_all_user(unsigned short ID)
 * \brief Supprime un utilisateur en particulier.
 */
void delete_user(unsigned short ID);

/**
 * \fn void delete_all_users()
 * \brief Supprime tous les utilisateurs.
 * En vue de la suppression du serveur.
 */
void delete_all_users();

#endif 
