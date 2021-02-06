CC=gcc
CFLAGS=-Wall

all: perdu oups

perdu: exo1.c
	$(CC) $(CFLAGS) -o $@ -DMSG="\"perdu\n\"" $<

oups: exo1.c
	$(CC) $(CFLAGS) -o $@ -DMSG="\"oups, encore perdu\n\"" $<

clean:
	rm -f perdu oups
