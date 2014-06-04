#include "error.h"

/*Ecrit un message d'erreur donne en parametre*/
void exit_message(char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}

/*Ecrit un message d'erreur*/
void error_message(char *msg){
	fprintf(stderr,"%s",msg);
	error=20;
}
