#include "log.h"

/*Ecrit un message d'erreur donne en parametre*/
void exit_message(char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}

/*Ouvre un fichier log contenant les messages de l'ID*/
int open_log(unsigned short ID, int OPEN){
	int fd;
	char name[50];
	char cast[5];

	snprintf(cast,5,"%d",ID);
	snprintf(name,12+strlen(cast),".login_%d.txt",ID);

	if(-1 == (fd=open(name,OPEN, 00744))){
		exit_message("error open file");
	}
	return fd;
}

/*Ecrit un message dans le log correspondant*/
void write_log(int fd, char *msg){
	if(-1 == write(fd,msg,strlen(msg))){
		exit_message("error writing in file");
	}
	if(-1 == write(fd,"\n",1)){
		exit_message("error writing back in file");
	}
}

/*Lit le log spécifie*/
void read_log(int fd){
	char buff;
	int result=1;

	while(0 != result){
		if(-1 == (result=read(fd,&buff,1))){
			exit_message("error reading file");
		}
		if (-1 == write(1, &buff, 1)) {
			exit_message("error writing stdout");
		}
	}
}

/*Ferme le fichier log*/
void close_log(int fd){
	if(-1 == close(fd)){
		exit_message("error close file");
	}
}

int writening_log(unsigned short ID, char *msg){
	int result,i,size=145;
	char *message;

	for(i=0 ; i < strlen(msg) ; i++){
		if(msg[i]=='\n'){
			size=i;
			break;
		}
	}
	message=malloc(sizeof(char)*size+1);
	snprintf(message,size+1,"%s",msg);

	result=open_log(ID,WRITE);
	write_log(result,message);
	close_log(result);
	return 0;
}

