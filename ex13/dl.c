#include <stdio.h>

// task2: fast modular exponentiation
// complexity: logx, also linear in the size of x
unsigned long fme(unsigned long g, unsigned long x, unsigned long p)
{
    unsigned long t;
    if(x == 0)
    {
        return 1; // g^0 = 1 mop p
    }
    // x is even
    if(x % 2 == 0)
    {
        t = fme(g, x/2, p); // recussive calculate g^(x/2)
        return (t*t) % p; // (g^(x/2))^2 = g^x
    }
    else
    {
        // odd: separate a g, g^x = g*g^(x-1)
        // recussive calculate g^((x-1)/2)
        t = fme(g, (x-1)/2, p);
        // g* (g^((x-1)/2))^2 = g*g^(x-1) = g^x 
        return (g*((t*t) % p)) % p;
    } 
}

// task3: discrete logarithm
// complexity: exponential: p = 2^n, n is number of bits, p*logp
// complexity for fme is logn but its reverse dl is exponential, so it is hard to invert
unsigned long dl(unsigned long y, unsigned long g, unsigned long p)
{
    unsigned long x = 0, result = 0;
    // x >=1, x < p
    for(x = 1; x < p; x++)
    {
        result = fme(g, x, p);
        if(result == y)
        {
            return x;
        }
    }
    return 0;
}

int main()
{
    printf("%ld\n", dl(3, 7, 10));
    printf("%ld\n", dl(10, 1, 11));
    return 0;
}