#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/select.h>
 
#define h_addr h_addr_list[0]
 
#define SIZE 256

void error_message(char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}
 
struct sockaddr_in init_socket(int port, char* name) {
    struct sockaddr_in sock;
    struct hostent *host_name;
 
    unsigned int i;
    if (port < 1024) {
        fprintf(stderr, "Port reserved for root\n");
        exit (EXIT_FAILURE);
    }
    sock.sin_family = AF_INET;
    sock.sin_port = htons(port);
    if (NULL == (host_name = gethostbyname(name))) {
        perror("gethostbyname");
        exit (EXIT_FAILURE);
    }
    sock.sin_addr.s_addr = ((struct in_addr *) (host_name->h_addr))->s_addr;
    for (i = 0; i < 8; i++) {
        sock.sin_zero[i] = '\0';
    }
    return sock;
}
 
int connect_socket(int port, char* name) {
    struct sockaddr_in sock;
    int fd,i, max_sd;
    int fd_connect;
    fd_set master_set;
    int read_size;
    char buffer[256]={0};
    sock = init_socket(port, name);
    if (-1 == (fd = socket(AF_INET, SOCK_STREAM, 0))) {
        perror("SOCKET");
        exit (EXIT_FAILURE);
    }
    if (-1
            == (fd_connect = connect(fd, (struct sockaddr*) &sock, sizeof(sock)))) {
        perror("CONNECT");
        exit (EXIT_FAILURE);
    }
   	if(-1 == write(1,"Communication ouverte avec le server\n",37)){
   		error_message("write");
   	}
    do {
        FD_ZERO(&master_set);
        max_sd = fd;
        FD_SET(fd, &master_set);
        FD_SET(STDIN_FILENO, &master_set);
 
        for(i = 0; i < SIZE ; i++){
            buffer[i] = '\0';
        }
        if(-1 == (select(max_sd +1, &master_set, NULL, NULL, NULL))) {
            perror("SELECT");
            exit(EXIT_FAILURE);
        }
 
            if(FD_ISSET(STDIN_FILENO, &master_set)){
                do {
                    if (-1 == (read_size = read(STDIN_FILENO, buffer, SIZE-6))) {
                        perror("read");
                        exit (EXIT_FAILURE);
                    }
                    if(read_size > SIZE-7) {
                        printf("Message trop long\n");
                    }
                }while(read_size > SIZE-7);
 
                strcat(buffer, "\n\0");
                send(fd, buffer, read_size+1, 0);
            }
            if(FD_ISSET(fd, &master_set)){
                if (-1 == (read_size = recv(fd, buffer, SIZE, 0))) {
                    perror("read");
                    exit (EXIT_FAILURE);
                }
                 
                if(-1 == write(STDOUT_FILENO, buffer, SIZE)){
                    perror("WRITE");
                    exit(EXIT_FAILURE);
                }
            }
    } while (1);
 
}
 
int main(int argc, char* argv[]) {
    int f;
    if (argc < 2) {
        fprintf(stderr, "Not enough arguments\n");
        exit (EXIT_FAILURE);
    }
 
    f = connect_socket(atoi(argv[1]), "localhost");
    close(f);
 
    return 0;
}