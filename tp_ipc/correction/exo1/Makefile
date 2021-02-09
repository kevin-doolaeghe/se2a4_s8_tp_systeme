CC=gcc
CFLAGS=-Wall

all: pong ping

pong: pong.c
	$(CC) $(CFLAGS)  -o $@ $<

ping: ping.c
	$(CC) $(CFLAGS)  -o $@ $<

clean:
	rm -f ping pong
