#include "follow.h"

unsigned char error;

/*Ecrit un message d'erreur*/
void error_message(char *msg){
	fprintf(stderr,msg);
	error=20;
}

/*Alloue l'espace necessaire d'un follow*/
Follow* allocate_follow(unsigned short ID){
	Follow *newFollow;

	if(NULL == (newFollow=malloc(sizeof(Follow)))){
		error_message("fol malloc");
		return NULL;
	}

	newFollow->ID=ID;
	newFollow->next=NULL;
	
	/*error=0;*/

	return newFollow;
}

/*Detruit tous les followers. En vue de la suppression d'un utilisateur*/
void free_all_follow(Follow **follow){
	Follow *temp;

	while(*follow!=NULL){
		temp=*follow;
		*follow=(*follow)->next;
		free(temp);
	}
	free(*follow);
	error=0;
	*follow=NULL;
}

/*Detruit un follower en particulier*/
void free_a_follow(Follow **follow, unsigned short ID){
	Follow *first=*follow;
	Follow *second;
	Follow *temp;

	if(first==NULL){
		error=32;
		return ;
	}
	
	second=first->next;

	if(first->ID==ID){
		*follow=second;
		free(first);
		error=0;
		return ;
	}
	
	while(second!=NULL){
		if(second->ID==ID){
			temp=second;
			first->next=second->next;
			free(temp);
			error=0;
			return ;
		}
		first=first->next;
		second=second->next;
	}
	error=30;
	return ;
}

/*Cherche un follower par mis ceux existant*/
int search_follow(Follow *follow, unsigned short ID){
	if(follow==NULL){
		return FALSE;
	}
	while(follow->next != NULL){
		if(follow->ID==ID){
			return TRUE;
		}
		follow=follow->next;
	}
	return FALSE;
}

/*Insere un nouveau follower */
void insert_follow(Follow **follow, Follow *fol){
	if( *follow==NULL ){
		*follow=fol;
		return ;
	}
	fol->next=*follow;
	*follow=fol;
}

/*Affiche tous les followers d'un ID*/
void print_follow(Follow *follow){
	Follow *tmp = follow;
	printf("lol \n");
	while (tmp != NULL) {
			fprintf(stdout, "ID : %d\n", tmp->ID );
			tmp = tmp->next;
	}
}

/*Ajoute un follower à un utilisateur*/
int add_follow(Follow **follow, unsigned short ID){
	if(search_follow(*follow,ID)==TRUE){
		error=22;
	}
	else{
		insert_follow(follow, allocate_follow(ID) );
	}
	return error;
}
