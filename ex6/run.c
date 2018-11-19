// main function

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#define MAX_LEN_STRING 26

extern void QuickSortString(char a[][MAX_LEN_STRING], int start, int end);
extern int BinarySearch(char a[][MAX_LEN_STRING], int len, char* target);
int getNextString(char *buffer, int size, FILE *stream);

int main()
{
    int n = 0; // number of strings
    scanf("%d", &n);
    int m = 0; // number of queries
    scanf("%d", &m);
    char str[n][MAX_LEN_STRING];
    char query[m][MAX_LEN_STRING];
    for(int i = 0; i < n; i++)
    {
        if(getNextString(str[i], MAX_LEN_STRING, stdin) == -1)
        {
            exit(-1);
        }
    }
    for(int i = 0; i < m; i++)
    {
        if(getNextString(query[i], MAX_LEN_STRING, stdin) == -1)
        {
            exit(-1);
        }
    }
    QuickSortString(str, 0, n-1);
    int searchResult = -1;
    for(int i = 0; i < m; i++)
    {
        searchResult = BinarySearch(str, n, query[i]);
        if(searchResult == -1)
        {
            printf("no ");
        }
        else
        {
            printf("yes ");
        }
    }
    return 0;
} 

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