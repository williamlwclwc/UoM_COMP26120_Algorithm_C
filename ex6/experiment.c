// main function

#include "search.h"

int main()
{
    clock_t start_t, end_t;
    double total_t1, total_t2, total_t, sort_t;
    int n = 0; // number of strings
    scanf("%d", &n);
    int m = 0; // number of queries
    scanf("%d", &m);
    char str[n][MAX_LEN_STRING]; // data for quick sort
    char strl[n][MAX_LEN_STRING]; // copy of original data
    char query[m][MAX_LEN_STRING];

    // read the data
    for(int i = 0; i < n; i++)
    {
        if(getNextString(str[i], MAX_LEN_STRING, stdin) == -1)
        {
            exit(-1);
        }
        strcpy(strl[i], str[i]);
    }
    for(int i = 0; i < m; i++)
    {
        if(getNextString(query[i], MAX_LEN_STRING, stdin) == -1)
        {
            exit(-1);
        }
    }

    // time of quick sort
    start_t = clock();
    QuickSortString(str, 0, n-1);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    sort_t = total_t;

    for(m = 1117; m <= 1137; m += 2)
    {
        // current value of m
        printf("m = %d\n", m);
        // binary search
        start_t = clock();
        int searchResult = -1;
        for(int i = 0; i < m; i++)
        {
            searchResult = BinarySearch(str, n, query[i]);
            if(searchResult == -1)
            {
                //printf("no ");
            }
            else
            {
                //printf("yes ");
            }
        }
        end_t = clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        // total time of binary search has to add time of sort
        total_t1 = total_t + sort_t;
        printf("Binary search time: %fs\n", total_t1);

        // linear search
        start_t = clock();
        int flag = 0;
        for(int i = 0; i < m; i++)
        {
            flag = 0;
            for(int j = 0; j < n; j++)
            {
                // use original data here
                if(strcmp(strl[j], query[i]) == 0)
                {
                    //printf("yes ");
                    // when found target we break to save time
                    flag = 1;
                    break;
                }
            }
            if(flag == 0)
            {
                //printf("no ");
            }
        }
        end_t = clock();
        // total time of linear search
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        total_t2 = total_t;
        printf("Linear search time: %fs\n", total_t2);
    }
    return 0;
} 