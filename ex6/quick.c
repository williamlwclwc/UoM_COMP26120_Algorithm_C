#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define array_size 1000000

// in place quick sort
int inPlacePartition(int a[], int start, int end)
{
    int temp;
    // select a random item in the array
    // range from start to end
    srand((unsigned) time(0));
    int r = rand() % (end - start + 1) + start;
    // swap a[r] & a[end]
    temp = a[r];
    a[r] = a[end];
    a[end] = temp;
    int pivot = a[end];
    // "left" point to the start
    int l = start;
    // "right" point to the end(except selected one)
    r = end - 1;
    // as long as "left" do not meet "right"
    while(l <= r)
    {
        // while left part < pivot, l moves on
        while(l <= r && a[l] <= pivot)
        {
            l++;
        }
        // while right part > pivot, r moves on
        while(r >= l && a[r] >= pivot)
        {
            r--;
        }
        // if both pointers stop, swap the numbers 
        if(l < r)
        {
            //swap a[l] & a[r]
            temp = a[l];
            a[l] = a[r];
            a[r] = temp;
        }
    }
    // l = r, pivot = a[end]
    //swap a[l] & a[end]: put pivot into final place
    temp = a[l];
    a[l] = a[end];
    a[end] = temp;
    return l;
}

void quick_sort(int a[], int start, int end)
{
    while(start < end)
    {
        int l = inPlacePartition(a, start, end);
        // left subarray is smaller
        // always sort the smaller one first to reduce the stack space
        if(l - start < end - l)
        {
            quick_sort(a, start, l - 1);
            // left part is sorted
            start = l + 1;
        }
        else
        {
            quick_sort(a, l + 1, end);
            // right part is sorted
            end = l - 1;
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
    quick_sort(array, 0, n-1);
    for(int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    //printf("Total time: %fs\n", total_t);
    return 0;
}

/* not working due to high space complexity
void quick_sort(int a[], int n)
{
    if(n < 2)
    {
        return;
    }
    int pivot = a[n-1];
    int n_l = 0, n_r = 0;
    for(int i = 0; i < n-1; i++)
    {
        if(a[i] <= pivot)
        {
            n_l++;
        }
        else
        {
            n_r++;
        }
    }
    int left[n_l], right[n_r];
    int i_l = 0, i_r = 0;
    for(int i = 0; i < n-1; i++)
    {
        if(a[i] <= pivot)
        {
            left[i_l] = a[i];
            i_l++;
        }
        else
        {
            right[i_r] = a[i];
            i_r++;
        }
    }
    quick_sort(left, n_l);
    quick_sort(right, n_r);
    int index = 0;
    for(int i = 0; i < n_l; i++)
    {
        a[index] = left[i];
        index++;
    }
    a[index] = pivot;
    index++;
    for(int i = 0; i < n_r; i++)
    {
        a[index] = right[i];
        index++;
    }
}
*/