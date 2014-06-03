#include <stdio.h>
#include "users.h"
#include "follow.h"
#include "log.h"

int main(void){
	int fd;
	init_users();
	numberOfUsers=51;
	printf("%d\n",create_user(5,"HELLBOY"));
	fd=open_log(21,WRITE);
	write_log(fd,"Hello guys");
	close_log(fd);
	fd=open_log(21,READ);
	read_log(fd);
	close_log(fd);
	return 0;
}