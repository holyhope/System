#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include "server.h"

#define BUFFER_SIZE 255

int main ( int argc, const char *argv[] ){
    int fd, size;
    pid_t pid;
    char buffer[BUFFER_SIZE];

    if ( -1 == ( fd = open( ".serverpid", O_RDONLY ) ) ) {
		perror( "open" );
		exit( EXIT_FAILURE );
    }
    if ( -1 == ( size = read( fd, buffer, BUFFER_SIZE ) ) ) {
		perror( "read" );
		exit( EXIT_FAILURE );
    }
    if ( size == BUFFER_SIZE ) {
		write(
		STDERR_FILENO,
		"Impossible de lire le PID",
		sizeof( char ) * strlen( "Impossible de lire le PID" )
		);
		exit( EXIT_FAILURE );
    }
    pid = atoi( buffer );

    if (-1 == kill( pid, SIGKILL ) ) {
        perror( "kill" );
        exit( EXIT_FAILURE );
    }

    close( fd );
    exit(EXIT_SUCCESS);
}

#undef BUFFER_SIZE
