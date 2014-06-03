#include "server.h"


/* obtenir une socket en ecoute */

int get_socket(unsigned short portnum){

	struct sockaddr_in listening_socket;
	int sockfd;

	/* creation de la socket */
	if(-1 == (sockfd = socket(AF_INET,SOCK_STREAM,0))){
		perror("get_socket: socket\t");
		exit(EXIT_FAILURE);
	}

	if(portnum <= 1024){
		perror("get_socket: portnum\t");
		exit(EXIT_FAILURE);
	}

	listening_socket.sin_family = AF_INET;
	listening_socket.sin_port = htons(portnum);
	listening_socket.sin_addr.s_addr = INADDR_ANY;

	/* liaison + ecoute */
    if (-1 == bind(sockfd,(struct sockaddr *)(&listening_socket),sizeof(struct sockaddr_in))){
        perror("get_socket: bind\t");
        exit(EXIT_FAILURE);
	}

	if(-1 == listen(sockfd,30)){
		perror("get_socket: listen\t");
		exit(EXIT_FAILURE);
	}

	return sockfd;
}

/*int client_connect()*/


extern void server_start(unsigned short portnum) {

	int sockfd,clientfd;

	if( -1 == ((sockfd = get_socket(portnum)))){
		perror("server_start: get_socket\t");
		exit(EXIT_FAILURE);
	}

	if(-1 == fprintf(stdout," Server OK...\n Looking for match\n")){
		perror("server_start: fprintf\t");
		exit(EXIT_FAILURE);
	}

	if(-1 == ((clientfd = accept(sockfd,NULL,NULL)))){
		perror("server_start: accept\t");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);

}


int get_datas(int sockfd,char *buf){
	int fd;
	int action;

	// action = send_request(sockfd,buf);	
	

	if( -1 ==( fd = recv(sockfd,buf,sizeof(buf),0))){
		perror("server: get_datas");
		return 1;

	}

	return 0;

}
/*

	switch(action) {
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







int begin(int argc,char *argv[]){

	unsigned short portnum;

	if(argc == 1)
		portnum = 1963;
	
	if(argc == 2 && argv[1] != "-d")
		portnum = atoi(argv[1]);

	if(argc == 2 && argv[1] == "-d")
		return 2;
	
	server_start(portnum);
	
/*
	if(serveur tourne deja)
		return 1;
*/

	return 0;
}


/*

int main(int argc, char *argv[]){

	int val;

	val = begin(argc,argv);

	exit(EXIT_SUCCESS);

}*/
