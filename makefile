CC = gcc
FLAGS = -Wall


all: client


client: client.c
			$(CC) $(FLAGS) client.c -o client



clean:
		rm -f a.out client