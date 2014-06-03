CC=gcc
CFLAGS= -Wall -ansi
OBJ=follow.o users.o main.o log.o

main: $(OBJ)
	$(CC) -o main $(OBJ) $(CFLAGS)

users.o: users.c users.h follow.h
	$(CC) -o users.o -c users.c $(CFLAGS) 

follow.o: follow.c follow.h
	$(CC) -o follow.o -c follow.c $(CFLAGS)

log.o: log.c log.h
	$(CC) -o log.o -c log.c $(CFLAGS)

main.o: main.c users.h follow.h
	$(CC) -c main.c $(CFLAGS) 

clean:
	rm *.o

rebuild:
	make clean
	make