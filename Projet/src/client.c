#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

typedef enum {
	NAM=220,
	ADD=201, 
	GET=224,
	FOL=225,
	FQR=233,
	CLE=212,
	ALL=217
}ACTION;
	
int connect_client(int sockfd){

	int clientfd;
	struct sockaddr_in socket;

	if(-1 == clientfd(connect(sockfd,(struct sockaddr *)(&socket),sizeof(struct sockaddr_in)))){
		perror("client: connect_client");
		exit(EXIT_FAILURE);

	}

	return clientfd;

}




int action_to_num(char *action){

	return action[0]+action[1]+action[2];

}	


int send_request(int sockfd,char *buf){

	int fd;
	int id;
	char action[3];
	char *newbuf;

	if(-1 == strncpy(action,3,buf)){
		perror("client: strncpy");
		return 1;
	}

	ACTION = action_to_num(action);

/*	switch(ACTION) {
		case NAM:
			if (-1 == send(sockfd,action,sizeof(action),0)){
				perror("client: NAM");
				return 1;
			}

		case ADD:

			if (-1 == send(sockfd,buf,sizeof(buf),0)){
				perror("client: ADD");
				return 1;

		case GET:
			if (-1 == send(sockfd,action,sizeof(action),0)){
				perror("client: GET");
				return 1;

		case FOL:
			if (-1 == send(sockfd,action,sizeof(action),0)){
				perror("client: FOL");
				return 1;
			}
			
		case FQR:
			if (-1 == send(sockfd,action,sizeof(action),0)){
				perror("client: FQR");
				return 1;
			}

		case CLE:
			if (-1 == send(sockfd,action,sizeof(action),0)){
				perror("client: CLE");
				return 1;
			}

		case ALL:
			if (-1 == send(sockfd,action,sizeof(action),0)){
				perror("client: ALL");
				return 1;
			}

	}
*/

	return ACTION;

}
