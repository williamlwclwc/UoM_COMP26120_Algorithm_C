#include <stdio.h>
#include <time.h>
#define Max_buckets 32768
#define array_size 1000000

void bucket_sort(int a[], int n)
{
    //buckets of size one： store number of the figure's appearance
    int buckets[Max_buckets];
    //initialize to 0
    for(int i = 0; i < Max_buckets; i++)
    {
        buckets[i] = 0;
    }
    //O(n): put into buckets
    for(int i = 0; i < n; i++)
    {
        (*(buckets + a[i]))++;
    }
    //get the results from buckets to array
    int index = 0;
    for(int i = 0; i < Max_buckets; i++)
    {
        for(int j = 0; j < buckets[i]; j++)
        {
            a[index] = i;
            index++;
        }
    }
}

int main()
{
    clock_t start_t, end_t;
    double total_t;
    start_t = clock();
    //input array
    int n = 0;
    scanf("%d", &n);
    int array[array_size];
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }
    //execute sort function
    bucket_sort(array, n);
    for(int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    //printf("Total time: %.3fs\n", total_t);
    return 0;
}