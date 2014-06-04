#include "data.h"
#include "server.h"
#include "users.h"
#include "log.h"

int main(int argc, char** argv) {
	int fd;
	if (argc != 2) {
		perror("arg invalid : ./feugueur portnum\n");
		exit (EXIT_FAILURE);
	}
	init_users();
	fd = create_socket(atoi(argv[1]));
	 
	close(fd);
	exit (EXIT_SUCCESS);
}
