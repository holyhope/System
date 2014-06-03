#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>

int create_socket(short port) {
    int sockfd;
    struct sockaddr_in sock;
    
    if (port < 1024) {
        fprintf(stderr, "error: specified port is reserved to the root\n");
        return -1;
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return -1;
    }
    sock.sin_family = AF_INET;
    sock.sin_port = htons(port);
    sock.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(&sock.sin_zero, 0, sizeof(sock.sin_zero));
    if (-1 == bind(sockfd, (struct sockaddr *) &sock, sizeof(sock))) {
        perror("bind");
        return -1;
    }
    if (-1 == listen(sockfd, 10)) {
        perror("listen");
        return -1;
    }
    return sockfd;
}


void error(char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
	int sockfd,portnum;
	struct sockaddr_in serv;

	if(argc<2){
		error("Invalid arguments");
	}

	if(0 > (sockfd=socket(AF_INET, SOCK_STREAM, 0))){
		error("socket failure");
	}



	exit(EXIT_SUCCESS);
}