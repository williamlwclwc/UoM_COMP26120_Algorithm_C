#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_SIZE 20

// task1: highest common factor
// complexity: linear in the size of a
unsigned long hcf(unsigned long a, unsigned long b)
{
    unsigned long r;
    if(b == 0)
    {
        return a;
    }
    else
    {
        r = a % b;
        return hcf(b, r);
    }
}

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
    // print out x binary
    // for(int j = 0; j < bits; j++)
    // {
    //     printf("%d", binary_x[j]);
    // }
    // printf("\n");
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

// task4: inverse modulo prime
// complexity: the same as task1, linear in the size of y
// xy + bp = gcd(y, p)
// if y and p are coprime, then gcd(y, p) = 1, xy + bp = 1 
// mod b: (xy + bp) mod p = 1 mod p -> xy mod p = 1 then we return x 
// we will need to extend task1: ax + by = gcd(a, b)
unsigned long hcf_2(unsigned long a, unsigned long b, long *x, long *y) 
{ 
    // Base Case 
    if (b == 0) 
    { 
        *x = 1, *y = 0; 
        return a; 
    } 

    long x1, y1; // To store results of recursive call 
    unsigned long gcd = hcf_2(b, a%b, &x1, &y1); 

    // Update x and y using results of recursive 
    *x = y1; 
    *y = x1 - (a/b) * y1; 

    return gcd; 
}

unsigned long imp(unsigned long y, unsigned long p)
{
    long x, b;
    unsigned long result = 0;
    unsigned long gcd = hcf_2(y, p, &x, &b);
    if(gcd != 1)
    {
        // inverse do not exist if not coprime
        printf("inverse modulo do not exist\n");
    }
    else
    {
        result = (x % p + p) % p; // handle if x < 0
    }
    return result;
}

// task5: El Game System
void elGame()
{
    // unsigned long p = 65537, g = 3;
    unsigned long p = 4093082899, g = 2;
    unsigned long pk = 0, a = 0, b = 0;
    char input[MAX_SIZE];
    while(1)
    {
        printf("Prime modulus is %lu\n", p);
        printf("Primitive root wrt %lu is %lu\n", p, g);
        printf("Choose: e (encrypt) | d (decrypt) | k (get public key) | x (exit)? ");
        scanf("%s", input);
        // get public key
        if(strcmp(input, "k") == 0 || strcmp(input, "get public key") == 0)
        {
            unsigned long x = 0;
            // 1 <= x < p
            while(x < 1 || x >= p)
            {
                printf("Type private key: ");
                scanf("%lu", &x);
            }
            pk = fme(g, x, p);
            printf("Public key is: %ld\n\n", pk);
        }
        // encrypt
        else if(strcmp(input, "e") == 0 || strcmp(input, "encrypt") == 0)
        {
            unsigned long M = 0;
            while(M < 1 || M >= p)
            {
                printf("Type secret number to send: ");
                scanf("%lu", &M);
            }
            if(pk != 0)
            {
                printf("public key saved in system: %ld\n", pk);
            }
            else
            {
                printf("maybe you should get public key first\n\n");
                continue;
            }
            printf("Type received public key: ");
            scanf("%lu", &pk);
            srand(time(0));
            unsigned long k = rand() % (p-1) + 1; // 1 <= k < p
            a = fme(g, k, p);
            b = ((M % p) * fme(pk, k, p)) % p;
            printf("The encrpyted secret is: (%ld,%ld)\n\n", a, b);
        }
        // decrypt
        else if(strcmp(input, "d") == 0 || strcmp(input, "decrypt") == 0)
        {
            char inString[MAX_SIZE];
            char aString[MAX_SIZE];
            char bString[MAX_SIZE];
            unsigned long x = 0, M;
            // parse encrypted secret string
            printf("Type in received message in form (a,b): ");
            scanf("%s", inString);
            int copy_ab = 0; // 0 copy a, 1 copy b
            int index_a = 0, index_b = 0, failed = 0;
            if(inString[0] != '(' || inString[strlen(inString)-1] != ')')
            {
                printf("illegal format, please try again\n\n");
                failed = 1;
                continue;
            }
            for(int i = 1; i < strlen(inString)-1; i++)
            {
                if(inString[i] == ',')
                {
                    // string b
                    copy_ab = 1;
                    continue;
                }
                else if(inString[i] < '0' || inString[i] > '9')
                {
                    printf("illegal format, please try again\n\n");
                    failed = 1;
                    break;
                }
                if(copy_ab == 0)
                {
                    aString[index_a] = inString[i];
                    index_a++;
                }
                else if(copy_ab == 1)
                {
                    bString[index_b] = inString[i];
                    index_b++;
                }
            }
            // if parsing is successful
            if(failed == 0)
            {
                aString[index_a] = '\0';
                bString[index_b] = '\0';
                a = atol(aString);
                b = atol(bString);
                // printf("(%lu,%lu)\n", a, b);
                // 1 <= x < p
                while(x < 1 || x >= p)
                {
                    printf("Type private key: ");
                    scanf("%lu", &x);
                }
                // decrypt M = a^(p-x-1)*b mod p
                M = ((b % p) * fme(a, p-x-1, p)) % p;
                printf("The decrypted secret is: %lu\n", M);
            }
            printf("\n");
        }
        else if(strcmp(input, "x") == 0 || strcmp(input, "exit") == 0)
        {
            printf("See you again\n");
            break;
        }
        else
        {
            printf("illegal command, please try again\n\n");
            continue;
        }
        
    }
}

int main()
{
    // printf("%ld\n", fme(7, 11, 10)); // test task2
    // printf("%ld\n", imp(3, 11)); // task4
    elGame();
    return 0;
}