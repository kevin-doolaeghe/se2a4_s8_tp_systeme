CC=gcc
CFLAGS=-Wall
LDFLAGS=-lpthread

all: serveur client

serveur: serveur.c
	$(CC) $(CFLAGS) $(LDFLAGS)  -o $@ $<

client: client.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f serveur client
