CC=gcc
CFLAGS=-Wall -g -std=c99
LDFLAGS=-lm

part1: 
	$(CC) $(CFLAGS) graph_functions.c part1.c -o part1 

part2:
	$(CC) $(CFLAGS) graph_functions.c part2.c -o part2

clean:
	rm -f part1 part2 part1.o part2.o graph_functions.o 

.PHONY: part1 part2
