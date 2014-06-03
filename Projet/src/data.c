#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#define MAX 30

typedef struct{
	int id;
	char *login;
}personne;

/* ---------------------------------------------------------------------NAM */

/*tableau de personnes connectees,jusqu'a 30 maximum simultanees*/
personne online[MAX];


void init_flow(personne online[MAX]){

	int i;
	for(i = 0; i < MAX; i ++){
		online[i].id = -1;
		online[i].login = "";
	}

}

int ajout_client(personne online[MAX],char *login){

	int i;
	for(i = 0; i < MAX; i++){
		if(online[i].id == -1){
			online[i].id = i;
			online[i].login = login;
			return i;
		}
	}
	return -1;

}

int deconnexion_client(personne online[MAX], int ID){

	online[ID].id = -1;
	online[ID].login = "";

	return 1;
}

void liste_client(personne online[MAX]){

	int i;
	
	for( i = 0; i < MAX; i++){
		if(online[i].id != -1)
			printf("%d:%s\n",online[i].id,online[i].login);
	}

	printf("\n");
}


/*-----------------------------------------------------------------------ADD */


ssize_t send(int sockfd, const void *buf, size_t len, int flags);

int tweet(char *buf, int sockfd){

	if ( strlen(buf) > 140 ){
		perror("data: tweet size");
		return 10;
	}

	if (-1 == send(sockfd,buf,(sizeof(buf)),0)){
		perror("data: tweet");
		return 10;
	}

	return 0;

}

/*
int main(int argc,char *argv[]){

char *a ="aaa";
char *b ="bbb";
char *c ="ccc";
int i;

int sockfd;

personne online[MAX] = {};

printf("hello\n");

init_flow(online);
i = ajout_client(online,a);
i = ajout_client(online,b);
i = ajout_client(online,c);

liste_client(online);

deconnexion_client(online,1);

liste_client(online);



return 0;
}*/



extern void data_init(void) {
	
}
