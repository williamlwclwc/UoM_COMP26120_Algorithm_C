#include <stdio.h>

// task2: fast modular exponentiation
// complexity: linear in the size of x
unsigned long fme(unsigned long g, unsigned long x, unsigned long p)
{
    unsigned long q = 0, result = 1, temp;
    const int bits = sizeof(unsigned long) * 8;
    // printf("bits: %d\n", bits);
    int i = bits - 1;
    int binary_x[bits];
    // transfer x into binary
    while(x != 0)
    {
        temp = x % 2;
        binary_x[i] = temp;
        i--;
        x = x / 2;
    }
    if(i > 0)
    {
        for(int j = i; j >= 0; j--)
        {
            binary_x[j] = 0;
        }
    }
    for(i = 0; i < bits; i++)
    {
        q = 2 * q;
        result = (result * result) % p;
        if(binary_x[i] == 1)
        {
            q++;
            result = (result * g) % p;
        }
    }
    return result;
}

// task3: discrete logarithm
// complexity: square size of p
unsigned long dl(unsigned long y, unsigned long g, unsigned long p)
{
    unsigned long x = 0, result = 0;
    // x >=1, x < p
    for(x = 1; x < p; x++)
    {
        result = fme(g, x, p);
        if(result == y)
        {
            break;
        }
    }
    return x;
}

int main()
{
    printf("%ld\n", dl(3, 7, 10));
    return 0;
}