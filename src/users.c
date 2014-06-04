#define _BSD_SOURCE
#include "users.h"

unsigned char error;

int truncate_string(char *msg){
	int i,size;
	for( i=0 ; i < strlen(msg)-1 ; i++){
		if( i != 0 && msg[i] == '\n' ){
			size = i;
			break;
		}
	}
	return size;
}

void init_users(){
	int i;

	numberOfUsers=0;
	for(i=0 ; i < MAX_USERS ; i++){
		connected[i].following=NULL;
	}
}

void swap_user(Users *first, Users *second){
	Users temp;

	temp=*first;
	*first=*second;
	*second=temp;
}

int create_user(unsigned short ID, char *login){
	int size=truncate_string(login);
	error=0;

	if(USERS_MAX(numberOfUsers)){
		error=70;
		return error;
	}
	connected[numberOfUsers].ID=ID;
	if ( NULL == (connected[numberOfUsers].login = malloc(sizeof(char)*size))) {
		error = 70;
	}
	if ( NULL == strncpy(connected[numberOfUsers].login,login,size) ) {
		/* A retoucher */
		error = 70;
	}
	numberOfUsers++;
	return error;
}

int search_user(unsigned short ID){
	int i;

	for( i=0 ; i < numberOfUsers ; i++){
		if(connected[i].ID==ID){
			return i;
		}
	}
	return -1;
}

void print_user(Users user, unsigned short ID){
	char message[SIZE_BUFFER];
	snprintf(message,strlen(user.login)+16,"--> %s (%d)\n",user.login,user.ID);
	if(-1 == send(ID, message, strlen(message), 0)){
        perror("SEND");
        exit(EXIT_FAILURE);
    }
}

void print_all_user(unsigned short ID){
	int i;

	for(i=0; i< numberOfUsers; i++) {
		print_user(connected[i],ID);
	}	
}

void delete_user(unsigned short ID){
	int num;

	if( -1 != (num=search_user(ID))){
		swap_user(&connected[num],&connected[numberOfUsers-1]);
		free_all_follow(&connected[numberOfUsers-1].following);
		free(connected[numberOfUsers-1].login);
		numberOfUsers--;
	} 
}

void delete_all_users(){
	int i;

	for(i=0 ; i< numberOfUsers ; i++){
		free_all_follow(&connected[i].following);
		free(connected[i].login);
	}
	numberOfUsers=0;
}
