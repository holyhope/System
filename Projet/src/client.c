#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT_DEFAULT 1963
#define ADDR_DEFAULT "localhost"

struct sockaddr_in get_socket( const char *host, int port ) {
	struct sockaddr_in s_addr;
	struct hostent *h;
	int size;

	if ( NULL == ( h = gethostbyname( host ) ) ) {
		perror( "gethostbyname" );
		exit( EXIT_FAILURE );
	}

	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons( port );
	s_addr.sin_addr = *( struct in_addr * ) h->h_addr;
	size = sizeof (struct sockaddr) - /* Remplissage */
		sizeof( sa_family_t ) - /* jusqu'a */
		sizeof( in_port_t ) - /* la taille de */
		sizeof( struct in_addr );

	memset( s_addr.sin_zero, 0, size );

	return s_addr;
}

struct sockaddr_in open_socket( const char *host, int port ) {
	struct sockaddr_in s_addr = get_socket( host, port );
	int sockfd = socket( AF_INET, SOCK_STREAM, 0 );
	if ( -1 == sockfd ) {
		perror( "socket" );
		exit( EXIT_FAILURE );
	}
	if ( -1 == connect( sockfd, (struct sockaddr *)&s_addr, sizeof( s_addr ) ) ) {
		perror( "connect" );
		exit( EXIT_FAILURE );
	}
	return s_addr;
}

int main( int argc, const char *argv[] ) {
	int size;
	int sockfd;
	int port = PORT_DEFAULT;
	struct sockaddr_in s_addr;
	char buffer[ BUFFER_SIZE ];

	if ( argc < 2 || argc > 3 ) {
		fprintf( stderr, "Usage: %s <adresse> [port]\n", *argv );
		return 1;
	}

	if ( argc == 3 ) {
		port = atoi( argv[2] );
	}

	sockfd = socket( AF_INET, SOCK_STREAM, 0 );
	s_addr = connect_socket( sockfd, argv[1], port );

	do {
		size = read( sockfd, buffer, BUFFER_SIZE );
		write( STDOUT_FILENO, buffer, size );
		if ( buffer[ size - 1 ] == EOF ) {
			break;
		}
		size = read ( STDIN_FILENO, buffer, BUFFER_SIZE );
		write ( sockfd, buffer, size );
	} while ( 1 );

	return 0;
}
