#include <stdio.h>
#define Max_buckets 35000

void bucket_sort(int a[], int n)
{
    //buckets of size one
    int buckets[Max_buckets];
    for(int i = 0; i < Max_buckets; i++)
    {
        buckets[i] = 0;
    }
    for(int i = 0; i < n; i++)
    {
        buckets[a[i]]++;
    }
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
    return 0;
}