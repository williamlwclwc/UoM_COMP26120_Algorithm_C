#include <stdio.h>
//#include <time.h>
#define array_size 1000000

void insertion_sort(int a[], int n)
{
    int j = 0;
    int temp = 0; //have to use temp for a[j+1] is a[i]
    for(int i = 1; i < n; i++)
    {
        temp = a[i]; //selected item(i): temp
        j = i-1; //j start form prior item to i
        //if temp > sorted items(j)
        while(a[j] > temp && j >= 0)
        {
            //move sorted items backwards
            a[j+1] = a[j];
            j--; //check next item until a[j]<temp or j<0
        }
        a[j+1] = temp; //put selected(i) in the right place
    }
}

int main()
{
    //clock_t start_t, end_t, total_t;
    //input array
    int n = 0;
    scanf("%d", &n);
    int array[array_size];
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }
    //start_t = clock();
    //execute sort function
    insertion_sort(array, n);
    for(int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    //end_t = clock();
    //total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    //printf("Total time: %.3ld\n", total_t);
    return 0;
}