#include <stdio.h>
#include <time.h>
#define array_size 1000000

void bubble_sort(int a[], int n)
{
    int temp = 0;
    //only need to make sure n-1 items are in the right place
    for(int i = 0; i < n-1; i++)
    {
        //the last i items are already sorted
        for(int j = 0; j < n-i-1; j++)
        {
            if(a[j] > a[j+1])
            {
                //swap a[j], a[j+1]
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
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
    bubble_sort(array, n);
    for(int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    //printf("Total time: %.3fs\n", total_t);
    return 0;
}