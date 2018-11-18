#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#define MAX_LEN_STRING 25

extern void QuickSortString(char a[][MAX_LEN_STRING], int start, int end);
extern int BinarySearch(char a[][MAX_LEN_STRING], int len, char* target);
int getNextString(char *buffer, int size, FILE *stream);

// referenced from "new_string_helper.h"
int getNextString(char *buffer, int size, FILE *stream) {

    int ch = fgetc(stream);
    // find the left quote
    while (ch != EOF && ch != '"')
        ch = fgetc(stream);

    // EOF or parsing error
    if (ch != '"')
        return -1;

    int nbytes = 0;
    const int maxSz = size-1;
    ch = fgetc(stream);
    while (nbytes != maxSz && ch != '"') {
        buffer[nbytes] = ch;
        ch = fgetc(stream);
        ++nbytes;
    }

    buffer[nbytes] = 0;
    return nbytes;
}