CC = gcc
CFLAGS = -Wall
LDFLAGS = -lcrypto


all: client server


client: client.o utilities.o communication.o
			$(CC) client.o utilities.o communication.o -o client


server: server.o crypt.o communication.o file_operations.o
			$(CC) server.o crypt.o communication.o file_operations.o -o server $(LDFLAGS)



client.o: client.c
			$(CC) $(CFLAGS) -c client.c

server.o: server.c
			$(CC) $(CFLAGS) -c server.c


utilities.o: utilities.c
				$(CC) $(CFLAGS) -c utilities.c

crypt.o: crypt.c
			$(CC) $(CFLAGS) -c crypt.c

communication.o: communication.c
					$(CC) $(CFLAGS) -c communication.c


file_operations.o: file_operations.c
					$(CC) $(CFLAGS) -c file_operations.c


clean:
		rm -f a.out *.o client server