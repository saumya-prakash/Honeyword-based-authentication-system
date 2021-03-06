CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lcrypto


all: client server honeychecker


# Create executables

client: client.o communication.o utilities.o
			$(CC) client.o communication.o utilities.o -o client



server: server.o crypt.o communication.o file_operations.o utilities.o
			$(CC) server.o crypt.o communication.o file_operations.o utilities.o -o server $(LDFLAGS)



honeychecker: honeychecker.o file_operations.o communication.o utilities.o
				$(CC) honeychecker.o file_operations.o communication.o utilities.o -o honeychecker



# Create object files

client.o: client.c
			$(CC) $(CFLAGS) -c client.c

server.o: server.c
			$(CC) $(CFLAGS) -c server.c

honeychecker.o: honeychecker.c
				$(CC) $(CFLAGS) -c honeychecker.c



crypt.o: crypt.c
			$(CC) $(CFLAGS) -c crypt.c


communication.o: communication.c
					$(CC) $(CFLAGS) -c communication.c


file_operations.o: file_operations.c
					$(CC) $(CFLAGS) -c file_operations.c



utilities.o: utilities.c
				$(CC) $(CFLAGS) -c utilities.c




# Delete the object files, executables
clean:
		rm -f a.out *.o client server honeychecker