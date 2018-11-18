#include <stdio.h>
#include <time.h>
#define array_size 1000000

void merge(int a[], int l1[], int l2[], int n1, int n2)
{
    int l[array_size];
    if(n1 == 0)
    {
        a = l2;
        return;
    }
    else if(n2 == 0)
    {
        a = l1;
        return;
    }
    int i1 = 0, i2 = 0;
    while(i1 < n1 && i2 < n2)
    {
        // put the smaller one into array l
        if(l1[i1] <= l2[i2])
        {
            l[i1 + i2] = l1[i1];
            i1++;
        }
        else
        {
            l[i1 + i2] = l2[i2];
            i2++;
        }
    }
    // if l1/l2 still has elements left
    while(i1 < n1)
    {
        l[i1 + i2] = l1[i1];
        i1++;
    }
    while(i2 < n2)
    {
        l[i1 + i2] = l2[i2];
        i2++;
    }
    // copy result into array a
    for(int i = 0; i < n1 + n2; i++)
    {
        a[i] = l[i];
    }
}

void merge_sort(int a[], int n)
{
    if(n <= 1)
        return;
    //split array into half
    int mid = n / 2;
    int* a1 = a; // part1: from 0-mid
    int* a2 = a + mid; // part2: form mid to n
    merge_sort(a1, mid); // result in a1
    merge_sort(a2, n-mid); // result in a2
    merge(a, a1, a2, mid, n-mid); // merge a1, a2, result in a
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
    merge_sort(array, n);
    for(int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    //printf("Total time: %fs\n", total_t);
    return 0;
}