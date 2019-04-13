CC=gcc
CFLAGS=-Wall -pedantic -g -std=c99
LDFLAGS=-lm

all: dl elGamal elGamalGMP


dl: dl.o 
	$(CC) $(CFLAGS) dl.o -o dl $(LDFLAGS)

elGamal: elGamal.o 
	$(CC) $(CFLAGS) elGamal.o -o elGamal $(LDFLAGS)

elGamalGMP: elGamalGMP.o 
	$(CC) $(CFLAGS) elGamalGMP.o -o elGamalGMP $(LDFLAGS)

clean:
	rm -rf *o dl elGamal elGamalGMP