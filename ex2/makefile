CC=gcc
CFLAGS=-g

arguments: part2a.c

test2a:
	./part2a #no parameters
	./part2a "only one parameter"
	./part2a "biggest parameter" "at" "start"
	./part2a "biggest" "parameter" "at" "end" "very very very big parameter"
	./part2a "answer" "somewhere" "in" "the" "middle"
	./part2a "two" "strings" "the" "same" "length" "ha ha !"
test2b:
	-./part2b #no parameters
	-./part2b -x 34
	-./part2b -c -bfs
	-./part2b -c -2000
	-./part2b -f -5000.0
	./part2b -f -27.0
	./part2b -c -16.6
