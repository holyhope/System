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

/**
 * \fn void exit_message(char *msg)
 * \brief Ecrit un message d'erreur puis quitte le programme.
 */
void exit_message(char *msg);

/**
 * \fn int open_log(unsigned short ID, int OPEN)
 * \brief Ouvre un fichier log contenant les messages de l'ID.
 */
int open_log(unsigned short ID, int OPEN);

/**
 * \fn void write_log(int fd, char *msg)
 * \brief Ecrit un message dans le log correspondant.
 */
void write_log(int fd, char *msg);

/**
 * \fn void read_log(int fd)
 * \brief Lit le log spécifié.
 */
void read_log(int fd);

/**
 * \fn void close_log(int fd)
 * \brief Ferme le fichier log.
 */
void close_log(int fd);

/**
 * \fn int writening_log(unsigned short ID, char *msg)
 * \brief Écrit un message dans le fichier log de l'utilisateur désigné par ID.
 */
int writening_log(unsigned short ID, char *msg);

#endif 
