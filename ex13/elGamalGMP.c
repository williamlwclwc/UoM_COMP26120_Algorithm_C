#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_SIZE 100

// task1: highest common factor
// complexity: linear in the size of a
void hcf(mpz_t result, mpz_t a, mpz_t b)
{
    mpz_t r;
    mpz_init(r);
    if(mpz_cmp_d(b, 0) == 0)
    {
        mpz_set(result, a);
    }
    else
    {
        mpz_mod(r, a, b);
        hcf(result, b, r);
    }
}

// task2: fast modular exponentiation
// complexity: logx, also linear in the size of x
void fme(mpz_t result, mpz_t g, mpz_t x, mpz_t p)
{
    // mpz_powm(result, g, x, p);
    mpz_t t, x_2, two;
    mpz_init(t);
    mpz_init(x_2);
    mpz_init(two);
    mpz_set_str(two, "2", 10);
    if(mpz_cmp_d(x, 0) == 0)
    {
        mpz_set_d(result, 1);
        return;
    }
    mpz_mod(t, x, two);
    if(mpz_cmp_d(t, 0) == 0)
    {
        // t = fme(g, x/2, p);
        // return (t*t) % p;
        mpz_set_str(x_2, "2", 10);
        mpz_div(x_2, x, x_2);
        fme(t, g, x_2, p);
        mpz_mul(t, t, t);
        mpz_mod(t, t, p);
        mpz_set(result, t);
    }
    else
    {
        // t = fme(g, (x-1)/2, p);
        // return (g*((t*t) % p)) % p;
        mpz_sub_ui(t, x, 1);
        mpz_set_str(x_2, "2", 10);
        mpz_div(x_2, t, x_2);
        fme(t, g, x_2, p);
        mpz_mul(t, t, t);
        mpz_mod(t, t, p);
        mpz_mul(t, g, t);
        mpz_mod(t, t, p);
        mpz_set(result, t);
    }
}

// task4: inverse modulo prime
// complexity: the same as task1, linear in the size of y
// xy + bp = gcd(y, p)
// if y and p are coprime, then gcd(y, p) = 1, xy + bp = 1 
// mod b: (xy + bp) mod p = 1 mod p -> xy mod p = 1 then we return x 
// we will need to extend task1: ax + by = gcd(a, b)
void hcf_2(mpz_t result, mpz_t a, mpz_t b, mpz_t x, mpz_t y) 
{ 
    // Base Case 
    if (mpz_cmp_d(b, 0) == 0) 
    { 
        mpz_set_str(x, "1", 10);
        mpz_set_str(y, "0", 10);
        mpz_set(result, a);
        return; 
    } 

    mpz_t x1, y1, gcd, r; // To store results of recursive call
    mpz_init(x1);
    mpz_init(y1);
    mpz_init(gcd);
    mpz_init(r);
    mpz_mod(r, a, b);
    hcf_2(gcd, b, r, x1, y1); 

    // Update x and y using results of recursive 
    mpz_set(x, y1);
    mpz_t temp;
    mpz_init(temp);
    mpz_div(temp, a, b);
    mpz_mul(temp, temp, y1);
    mpz_sub(y, x1, temp);
    // *y = x1 - (a/b) * y1; 

    mpz_set(result, gcd); 
}

void imp(mpz_t return_val, mpz_t y, mpz_t p)
{
    mpz_t x, b, gcd, result;
    mpz_init(x);
    mpz_init(b);
    mpz_init(gcd);
    mpz_init(result);
    mpz_set_str(result, "0", 10);
    hcf_2(gcd, y, p, x, b);
    if(mpz_cmp_d(gcd, 1) != 0)
    {
        // inverse do not exist if not coprime
        printf("inverse modulo do not exist\n");
    }
    else
    {
        mpz_mod(x, x, p);
        mpz_add(x, x, p);
        mpz_mod(result, x, p);
        // result = (x % p + p) % p; // handle if x < 0
    }
    mpz_set(return_val, result);
}

// task5: El Game System
void elGame()
{
    mpz_t p, g, a, b, pk;
    mpz_init(p);
    mpz_init(g);
    // mpz_set_str(p, "65537", 10);
    // mpz_set_str(g, "3", 10);
    mpz_set_str(p, "170141183460469231731687303715884105727", 10);
    mpz_set_str(g, "43", 10);
    mpz_init(a);
    mpz_init(b);
    mpz_init(pk);
    mpz_set_str(a, "0", 10);
    mpz_set_str(b, "0", 10);
    mpz_set_str(pk, "0", 10);
    char input[MAX_SIZE];
    while(1)
    {
        gmp_printf("Prime modulus is %Zd\n", p);
        gmp_printf("Primitive root wrt %Zd is %Zd\n", p, g);
        printf("Choose: e (encrypt) | d (decrypt) | k (get public key) | x (exit)? ");
        scanf("%s", input);
        // get public key
        if(strcmp(input, "k") == 0 || strcmp(input, "get public key") == 0)
        {
            mpz_t x;
            mpz_init(x);
            mpz_set_str(x, "0", 10);
            // 1 <= x < p
            while(mpz_cmp_d(x, 1) < 0 || mpz_cmp(x, p) >= 0)
            {
                printf("Type private key: ");
                scanf("%s", input);
                mpz_set_str(x, input, 10);
            }
            fme(pk, g, x, p);
            gmp_printf("Public key is: %Zd\n\n", pk);
        }
        // encrypt
        else if(strcmp(input, "e") == 0 || strcmp(input, "encrypt") == 0)
        {
            mpz_t M;
            mpz_init(M);
            mpz_set_str(M, "0", 10);
            while(mpz_cmp_d(M, 1) < 0 || mpz_cmp(M, p) >= 0)
            {
                printf("Type secret number to send: ");
                scanf("%s", input);
                mpz_set_str(M, input, 10);
            }
            if(mpz_cmp_d(pk, 0) != 0)
            {
                // gmp_printf("public key saved in system: %Zd\n", pk);
            }
            else
            {
                printf("maybe you should get public key first\n\n");
                continue;
            }
            printf("Type received public key: ");
            scanf("%s", input);
            mpz_set_str(pk, input, 10);
            srand(time(0));
            mpz_t k, p_1;
            mpz_init(k);
            mpz_init(p_1);
            mpz_sub_ui(p_1, p, 1);
            mpz_set_ui(k, rand());
            mpz_mod(k, k, p_1);
            mpz_add_ui(k, k, 1);
            // unsigned long k = rand() % (p-1) + 1; // 1 <= k < p
            fme(a, g, k, p);
            fme(p_1, pk, k, p);
            mpz_mod(M, M, p);
            mpz_mul(M, M, p_1);
            mpz_mod(b, M, p);
            // b = ((M % p) * fme(pk, k, p)) % p;
            gmp_printf("The encrpyted secret is: (%Zd,%Zd)\n\n", a, b);
        }
        // decrypt
        else if(strcmp(input, "d") == 0 || strcmp(input, "decrypt") == 0)
        {
            char inString[MAX_SIZE];
            char aString[MAX_SIZE];
            char bString[MAX_SIZE];
            mpz_t x, M;
            mpz_init(x);
            mpz_init(M);
            mpz_set_str(x, "0", 10);
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
                mpz_set_str(a, aString, 10);
                mpz_set_str(b, bString, 10);
                // a = atol(aString);
                // b = atol(bString);
                // 1 <= x < p
                while(mpz_cmp_d(x, 1) < 0 || mpz_cmp(x, p) >= 0)
                {
                    printf("Type private key: ");
                    scanf("%s", input);
                    mpz_set_str(x, input, 10);
                }
                // decrypt M = a^(p-x-1)*b mod p
                mpz_mod(b, b, p);
                mpz_t p_x_1;
                mpz_init(p_x_1);
                mpz_sub(p_x_1, p, x);
                mpz_sub_ui(p_x_1, p_x_1, 1);
                fme(p_x_1, a, p_x_1, p);
                mpz_mul(b, b, p_x_1);
                mpz_mod(M, b, p);
                // M = ((b % p) * fme(a, p-x-1, p)) % p;
                gmp_printf("The decrypted secret is: %Zd\n", M);
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
    elGame();
    return 0;

    // hcf test
    // mpz_t a, b, ans;
    // mpz_init(a);
    // mpz_init(b);
    // mpz_init(ans);
    // mpz_set_str(a, "30", 10);
    // mpz_set_str(b, "20", 10);
    // // hcf(ans, a, b);
    // mpz_t x, y;
    // mpz_init(x);
    // mpz_init(y);
    // hcf_2(ans, a, b, x, y);
    // gmp_printf("HCF: %Zd %Zd %Zd\n", ans, x, y);

    // fme test
    // mpz_t g, x, p, ans;
    // mpz_init(g);
    // mpz_init(x);
    // mpz_init(p);
    // mpz_init(ans);
    // mpz_set_str(g, "7", 10);
    // mpz_set_str(x, "11", 10);
    // mpz_set_str(p, "10", 10);
    // fme(ans, g, x, p);
    // gmp_printf("fme: %Zd\n", ans);

    // imp test
    // mpz_t y, p, ans;
    // mpz_init(y);
    // mpz_init(p);
    // mpz_init(ans);
    // mpz_set_str(y, "11", 10);
    // mpz_set_str(p, "10", 10);
    // imp(ans, y, p);
    // gmp_printf("ime: %Zd\n", ans);
}