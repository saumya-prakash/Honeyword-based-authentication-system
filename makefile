CC = gcc
CFLAGS = -Wall
LDFLAGS = -lcrypto


all: client 


client: client.o utilities.o communication.o
			$(CC) client.o utilities.o communication.o -o client





client.o: client.c
			$(CC) $(CFLAGS) -c client.c


utilities.o: utilities.c
				$(CC) $(CFLAGS) -c utilities.c

crypt.o: crypt.c
			$(CC) $(CFLAGS) -c crypt.c

communication.o: communication.c
					$(CC) $(CFLAGS) -c communication.c



clean:
		rm -f a.out *.o client