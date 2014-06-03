#include "users.h"

unsigned char error;

/*Permet d'initialiser la structure d'utilisateur*/
void init_users(){
	int i;

	numberOfUsers=0;
	for(i=0 ; i < MAX_USERS ; i++){
		connected[i].following=NULL;
	}
}

/*Echange dans la liste deux utilisateurs*/
void swap_user(Users *first, Users *second){
	Users temp;

	temp=*first;
	*first=*second;
	*second=temp;
}

/*Creer un utilisateur */
int create_user(unsigned short ID, char *login){
	error=0;
	if(SIZE_MAX(numberOfUsers)){
		error=70;
		return error;
	}
	connected[numberOfUsers].ID=ID;
	if(NULL == (connected[numberOfUsers].login = malloc(sizeof(char)*strlen(login)+1))) {
		error = 70;
	}
	if(NULL==strncpy(connected[numberOfUsers].login,login,strlen(login)+1)){
		/* A retoucher */
		error=70;
	}
	numberOfUsers++;
	return error;
}

/*Recherche un utilisateur existant*/
int search_user(unsigned short ID){
	int i;

	for( i=0 ; i < numberOfUsers ; i++){
		if(connected[i].ID==ID){
			return i;
		}
	}
	return -1;
}

/*Affiche un utilisateur en particulier*/
void print_user(Users user){
	printf("Id: %d login : %s\n", user.ID, user.login);
}

/*Affiche tous les utilisateurs*/
void print_all_user(){
	int i;

	for(i=0; i< numberOfUsers; i++) {
		print_user(connected[i]);
	}
	
}

/*Supprime un utilisateur en particulier*/
void delete_user(unsigned short ID){
	int num;

	if( -1 != (num=search_user(ID))){
		swap_user(&connected[num],&connected[numberOfUsers-1]);
		free_all_follow(&connected[numberOfUsers-1].following);
		free(connected[numberOfUsers-1].login);
		numberOfUsers--;
	} 
}

/*Supprime tous les utilisateurs. En vue de la suppression du serveur*/
void delete_all_users(){
	int i;

	for(i=0 ; i< numberOfUsers ; i++){
		free_all_follow(&connected[i].following);
		free(connected[i].login);
	}
	numberOfUsers=0;
}