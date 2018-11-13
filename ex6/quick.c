#include <stdio.h>
#include <time.h>
#define array_size 1000000

// in place quick sort
int inPlacePartition(int a[], int start, int end)
{
    int temp;
    int r = end;
    // swap a[r] & a[end]
    temp = a[r];
    a[r] = a[end];
    a[end] = temp;
    int p = a[end];
    int l = start;
    r = end - 1;
    while(l <= r)
    {
        while(l <= r && a[l] <= p)
        {
            l++;
        }
        while(r >= l && a[r] >= p)
        {
            r--;
        }
        if(l < r)
        {
            //swap a[l] & a[r]
            temp = a[l];
            a[l] = a[r];
            a[r] = temp;
        }
    }
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
        if(l - start < end - l)
        {
            quick_sort(a, start, l - 1);
            start = l + 1;
        }
        else
        {
            quick_sort(a, l + 1, end);
            end = l - 1;
        }
    }
}

int main()
{
    clock_t start_t, end_t;
    double total_t;
    //input array
    int n = 0;
    scanf("%d", &n);
    int array[array_size];
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }
    start_t = clock();
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