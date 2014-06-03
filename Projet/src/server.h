#ifndef __SERVER_H
#define __SERVER_H

typedef enum {
	NAM=220,
	ADD=201, 
	GET=224,
	FOL=225,
	FQR=233,
	CLE=212,
	ALL=217
} ACTION;

int get_socket( unsigned short portnum );

void server_start( unsigned short portnum );

#endif /* __SERVER_H */
