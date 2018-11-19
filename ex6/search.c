// search function

#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LEN_STRING 26

// in place quick sort
int inPlacePartitionString(char a[][MAX_LEN_STRING], int start, int end)
{
    char temp[MAX_LEN_STRING];
    char pivot[MAX_LEN_STRING];
    // select a random item in the array
    // range from start to end
    srand((unsigned) time(0));
    int r = rand() % (end - start + 1) + start;
    // swap a[r] & a[end]
    strcpy(temp, a[r]);
    strcpy(a[r], a[end]);
    strcpy(a[end], temp);
    strcpy(pivot, a[end]);
    // "left" point to the start
    int l = start;
    // "right" point to the end(except selected one)
    r = end - 1;
    // as long as "left" do not meet "right"
    while(l <= r)
    {
        // while left part < pivot, l moves on
        while(l <= r && strcmp(a[l], pivot) <= 0)
        {
            l++;
        }
        // while right part > pivot, r moves on
        while(r >= l && strcmp(a[r], pivot) >= 0)
        {
            r--;
        }
        // if both pointers stop, swap the numbers 
        if(l < r)
        {
            //swap a[l] & a[r]
            strcpy(temp, a[l]);
            strcpy(a[l], a[r]);
            strcpy(a[r], temp);
        }
    }
    // l = r, pivot = a[end]
    //swap a[l] & a[end]: put pivot into final place
    strcpy(temp, a[l]);
    strcpy(a[l], a[end]);
    strcpy(a[end], temp);
    return l;
}

void QuickSortString(char a[][MAX_LEN_STRING], int start, int end)
{
    while(start < end)
    {
        int l = inPlacePartitionString(a, start, end);
        // left subarray is smaller
        // always sort the smaller one first to reduce the stack space
        if(l - start < end - l)
        {
            QuickSortString(a, start, l - 1);
            // left part is sorted
            start = l + 1;
        }
        else
        {
            QuickSortString(a, l + 1, end);
            // right part is sorted
            end = l - 1;
        }
    }
}

int BinarySearch(char a[][MAX_LEN_STRING], int len, char* target)
{
    int front = 0;
    int back = len - 1;
    while(front <= back)
    {
        int mid = (front + back) / 2;
        if(strcmp(a[mid], target) > 0)
        {
            back = mid - 1;
        }
        else if(strcmp(a[mid], target) < 0)
        {
            front = mid + 1;
        }
        else
        {
            return mid;
        }
    } 
    return -1; // not found
}