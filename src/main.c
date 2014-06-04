#include <stdio.h>
#include "users.h"
#include "follow.h"
#include "server.h"
 
int main(int argc, char* argv[]) {
    int fd;
    if (argc != 2) {
        fprintf(stderr, "Usage: ./ex2 <port>\n");
        exit (EXIT_FAILURE);
    }
    init_users();
    fd = create_socket(atoi(argv[1]));
     
    close(fd);
    exit (EXIT_SUCCESS);
}