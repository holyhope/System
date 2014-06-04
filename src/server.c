#define _BSD_SOURCE
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include "server.h"
#include "log.h"
 
#define LENGTH 32
#define SIZE 256
#define BUFFER_SIZE 256

fd_set master_set;
int max_sd;

typedef enum{NAM,ADD,GET,FOL,FQR,CLE,ALL,END,NONE} Command;

Command command;

void send_message(int fd, char *buffer){
    int ID=search_user(fd);
    char message[BUFFER_SIZE];
    int i,size = truncate_string( buffer );

    size = snprintf( message, BUFFER_SIZE, "[%s] %s" , connected[ID].login, buffer );
    writing_log(fd,message);

    for(i=4 ; i < max_sd ; i++ ){
        if(FD_ISSET(i,&master_set) && i!=fd && search_follow(connected[ID].following,fd)){
            if(-1 == send(i,message,size,0)){
                perror("SEND");
                exit(EXIT_FAILURE);
            }
        }
    }
}

char* parser(char *buffer){
    char *msg;
    int size=truncate_string(buffer);
    int i;
    command=-1;
    msg=malloc(sizeof(char)*size-4);

    for(i=0 ; i < size-4 ; i++){
        msg[i]=buffer[i+4];
    }
    
    if(strncmp(buffer,"NAM",3)==0){
        command = NAM;
    } else if(strncmp(buffer,"ADD",3)==0){
        command = ADD;
    } else if(strncmp(buffer,"GET",3)==0){
        command = GET;
    } else if(strncmp(buffer,"FOL",3)==0){
        command = FOL;
    } else if(strncmp(buffer,"FQR",3)==0){
        command = FQR;
    } else if(strncmp(buffer,"CLE",3)==0){
        command = CLE;
    } else if(strncmp(buffer,"ALL",3)==0){
        command = ALL;
    } else if(strncmp(buffer,"END",3)==0){
        command = END;
    }
    return msg;
}

void command_send(int fd, char *buffer){
    int size;
    char msg[BUFFER_SIZE];
    int ID=search_user(fd);

    switch(command) {
        case NAM: 
            if (-1 == send( fd,"List of connected\n",20, 0 ) ) {
                perror( "SEND" );
                exit( EXIT_FAILURE );
            }
            print_all_user(fd);
            break;
        case ADD:
            send_message(fd,buffer);
            break;
        case GET: 
            size=truncate_string(buffer);
            snprintf(msg,size,"%s",buffer);
            reading_log(strtol(msg,NULL,10));
            break;
        case FOL: 
            size=truncate_string(buffer);
            snprintf(msg,size,"%s",buffer);
            add_follow(&connected[ID].following,strtol(msg,NULL,10));
            break;
        case FQR: 
            break;
        case CLE: 
            free_all_follow(&connected[search_user(fd)].following);
            break;
        case ALL:
			break;
        case END:
            delete_user(fd);
            exit(EXIT_SUCCESS);
            break;
        default: break;

    }
    command = NONE;
}
 
struct sockaddr_in init_socket(int port) {
    struct sockaddr_in sock;
    int i;
    if (port < 1024) {
        fprintf(stderr, "Port\n");
        exit (EXIT_FAILURE);
    }
    sock.sin_family = AF_INET;
    sock.sin_port = htons(port);
    sock.sin_addr.s_addr = INADDR_ANY;
    for (i = 0; i < 8; i++) {
        sock.sin_zero[i] = '\0';
    }
 
    return sock;
}
 
int create_socket(int port) {
    struct sockaddr_in sockaddr = init_socket(port);
    int  rc;
    char buffer[BUFFER_SIZE];
    char *message;
    fd_set working_set;
    struct timeval timeout;
    int listen_sd,new_sd;
    int i, j, len;

    /* char nickname_array[30][100]={{'\0'}}; */
    char askNickName[26];
 
     
    socklen_t size = sizeof(sockaddr);
    if (-1 == (listen_sd = socket(AF_INET, SOCK_STREAM, 0))) {
        perror("socket");
        exit (EXIT_FAILURE);
    }
 
    if (-1 ==  bind(listen_sd, (struct sockaddr*) &sockaddr, sizeof(sockaddr))) {
        perror("bind");
        exit (EXIT_FAILURE);
    }
    if (-1 ==  listen(listen_sd, LENGTH)) {
        perror("listen");
        exit (EXIT_FAILURE);
    }
    FD_ZERO(&master_set);
    max_sd = listen_sd;
    FD_SET(listen_sd, &master_set);
 
    timeout.tv_sec  = 3 * 60;
    timeout.tv_usec = 0;
 
    sprintf(askNickName, "En\n");
    do {
 
        memcpy(&working_set, &master_set, sizeof(master_set));
 
         
        if(-1 == (rc = select(max_sd + 1, &working_set, NULL, NULL, &timeout))){
            perror("SELECT");
            exit(EXIT_FAILURE);
        }
         
     
        for(i = 0; i <= max_sd; i++){
            if(FD_ISSET(i, &working_set)){
                /* PREMIERE CONNEXION */
                if(i == listen_sd){
                    printf("  Listening socket is readable\n");
                    if(-1 == (new_sd = accept(listen_sd, (struct sockaddr*) &sockaddr, &size))){
                        break;
                    }
                    printf("  New incoming connection - %d\n", new_sd);
                    FD_SET(new_sd, &master_set);
                    if(new_sd > max_sd)
                        max_sd = new_sd;
                    if(-1 == (rc = send(new_sd, askNickName, strlen(askNickName), 0))){
                            perror("SEND");
                            exit(EXIT_FAILURE);
                    }
                }
                else{
                    for(j = 0; j < BUFFER_SIZE; j++){
                        buffer[j]= '\0';
                    }
                    strcpy(buffer, "\0");
                    printf("  Descriptor %d is readable\n", i);
                    if(-1 == (rc = recv(i, buffer, sizeof(buffer), 0))){
                        perror("RECV");
                        exit(EXIT_FAILURE);
                    }
                    if(rc == 0){
                        close(i);
                        printf("  Connection closed by client\n");
                        FD_CLR(i, &master_set);
                        if(i == max_sd){
                            while(FD_ISSET(max_sd, &master_set) == 0)
                                max_sd --;
                        }
                        delete_user(i);
                        break;
                    }
                    len = rc;
                    printf("  %d bytes received\n", len);
                    if(search_user(i)==-1){
                        create_user(i,buffer);
                        printf("New nickname: <%s> ! for %d\n", connected[search_user(i)].login, i);
                    }
 
                    else{
                        message = parser(buffer);
                        command_send(i,message);
                    }
                }
 
            }
        }
    }while(1);     
     
    close(listen_sd);
 
    return listen_sd;
}
