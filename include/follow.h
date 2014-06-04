#ifndef _FOLLOW_H
#define _FOLLOW_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * \file follow.h
 * \brief Gestion du suivi de personnes.
 * Gestion du suivi des personnes grâce à des listes chaînées.
 */

#define TRUE 1
#define FALSE 0

typedef unsigned short ident;

/**
 * \struct Follow follow.h
 * \brief Contient la listes des ids des personnes que l'utilisateur suit.
 */
typedef struct fol{
	unsigned short ID; /*!< Identifiant du follower. */
	struct fol *next; /*!< Adresse vers la liste des prochains followers. */
} Follow;

/**
 * \fn void error_message(char *msg)
 * \brief Ecrit un message d'erreur.
 */
void error_message(char *msg);

/**
 * \fn Follow* allocate_follow(unsigned short ID)
 * \brief Alloue l'espace nécessaire à un suivi.
 */
Follow* allocate_follow(unsigned short ID);

/**
 * \fn void free_all_follow(Follow **follow)
 * \brief Supprime tous les fllows d'un utilisateur.
 * Généralement pour ensuite supprimer un utilisateur.
 */
void free_all_follow(Follow **follow);

/**
 * \fn void free_a_follow(Follow **follow, unsigned short ID)
 * \brief Arrète le suivi d'une personne.
 */
void free_a_follow(Follow **follow, unsigned short ID);

/**
 * \fn int search_follow(Follow *follow, unsigned short ID)
 * \brief Cherche une personne parmis les followers.
 */
int search_follow(Follow *follow, unsigned short ID);

/**
 * \fn void insert_follow(Follow **follow, Follow *fol)
 * \brief Insere une nouvelle personne dans une liste des personnes suivies.
 */
void insert_follow(Follow **follow, Follow *fol);

/**
 * \fn void insert_follow(Follow **follow, Follow *fol)
 * \brief Affiche tous les followers.
 */
void print_follow(Follow *follow);

/**
 * \fn int add_follow(Follow **follow, unsigned short ID)
 * \brief Ajoute un follower à un utilisateur.
 */
int add_follow(Follow **follow, unsigned short ID);

#endif
