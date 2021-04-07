CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lcrypto


all: client server


# Commmands for creating the executables

client: client.o communication.o
			$(CC) client.o communication.o -o client



server: server.o crypt.o communication.o file_operations.o utilities.o
			$(CC) server.o crypt.o communication.o file_operations.o utilities.o -o server $(LDFLAGS)





# Commands for creating object files

client.o: client.c
			$(CC) $(CFLAGS) -c client.c

server.o: server.c
			$(CC) $(CFLAGS) -c server.c


crypt.o: crypt.c
			$(CC) $(CFLAGS) -c crypt.c


communication.o: communication.c
					$(CC) $(CFLAGS) -c communication.c


file_operations.o: file_operations.c
					$(CC) $(CFLAGS) -c file_operations.c



utilities.o: utilities.c
				$(CC) $(CFLAGS) -c utilities.c




# deleting the object file, executables
clean:
		rm -f a.out *.o client server