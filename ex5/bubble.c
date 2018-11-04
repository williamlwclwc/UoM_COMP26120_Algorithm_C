#include <stdio.h>

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
    //read file 'in'

    //execute sort function

    //calculate running time

    //compare the results
    return 0;
}