#include <stdio.h>

void insertion_sort(int a[], int n)
{
    int j = 0, temp = 0;
    for(int i = 0; i < n; i++)
    {
        j = i-1; //j start form prior item to i
        //if selected item(i) > sorted items(j)
        while(a[j] > a[i] && j >= 0)
        {
            //move sorted items backwards
            a[j+1] = a[j];
            j--; //check next item until j<i or j<0
        }
        a[j+1] = a[i]; //put selected(i) in the right place
    }
}

int main()
{
    return 0;
}