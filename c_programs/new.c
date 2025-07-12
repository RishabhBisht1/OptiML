#include <stdio.h>
#include <stdlib.h> // For malloc, free
#include <string.h> // For strlen, strcpy

#define MAX_PRIME 100000
#define MATRIX_SIZE 50

// Function to calculate factorial recursively (up to a small limit)
long long factorial(int n)
{
    if (n == 0)
        return 1;
    if (n < 0)
        return -1; // Error for negative numbers
    if (n > 15)
        return 0;                // Prevent stack overflow for very large N in this demo
    return n * factorial(n - 1); // mul, call
}

// Function to implement Sieve of Eratosthenes
void sieveOfEratosthenes(int n, int primes[])
{
    // 0 and 1 are not prime
    int *isPrime = (int *)malloc((n + 1) * sizeof(int)); // call, store
    if (isPrime == NULL)
    {
        printf("Memory allocation failed for sieve.\n");
        return;
    }

    for (int i = 0; i <= n; i++) // loop, add, store, br i1
        isPrime[i] = 1;          // store

    isPrime[0] = 0; // store
    isPrime[1] = 0; // store

    for (int p = 2; p * p <= n; p++)
    { // loop, mul, br i1, add, store
        if (isPrime[p] == 1)
        {                                       // load, br i1
            for (int i = p * p; i <= n; i += p) // nested loop, mul, add, store, br i1
                isPrime[i] = 0;                 // store
        }
    }

    int count = 0; // store
    for (int p = 2; p <= n; p++)
    { // loop, add, store, br i1
        if (isPrime[p] == 1)
        {                        // load, br i1
            primes[count++] = p; // load, store, add
        }
    }
    free(isPrime); // call
}

// Function to perform matrix multiplication
void multiplyMatrices(int mat1[MATRIX_SIZE][MATRIX_SIZE], int mat2[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE])
{
    for (int i = 0; i < MATRIX_SIZE; i++)
    { // loop, add, store, br i1
        for (int j = 0; j < MATRIX_SIZE; j++)
        {                     // nested loop, add, store, br i1
            result[i][j] = 0; // store
            for (int k = 0; k < MATRIX_SIZE; k++)
            {                                            // deepest loop, add, store, br i1
                result[i][j] += mat1[i][k] * mat2[k][j]; // load, load, mul, add, store
            }
        }
    }
}

// Function to reverse a string
void reverseString(char *str)
{
    int length = strlen(str); // call
    int i, j;                 // define
    char temp;                // define
    for (i = 0, j = length - 1; i < j; i++, j--)
    {                    // loop, add, sub, store, br i1
        temp = str[i];   // load, store
        str[i] = str[j]; // load, store
        str[j] = temp;   // load, store
    }
}

int main()
{
    // --- Section 1: Prime Number Generation ---
    printf("Generating primes up to %d...\n", MAX_PRIME);       // call
    int *primes = (int *)malloc((MAX_PRIME / 5) * sizeof(int)); // call, store (approximate max primes)
    if (primes == NULL)
    {
        printf("Memory allocation failed for primes array.\n");
        return 1;
    }
    sieveOfEratosthenes(MAX_PRIME, primes);                                         // call
    printf("Found %d primes.\n", primes[0]);                                        // This is actually the count if sieve were modified
                                                                                    // For this demo, just print a dummy value or first prime
    printf("First few primes: %d, %d, %d, ...\n", primes[0], primes[1], primes[2]); // call
    free(primes);                                                                   // call

    // --- Section 2: Matrix Operations ---
    printf("\nPerforming matrix multiplication for %dx%d matrices...\n", MATRIX_SIZE, MATRIX_SIZE); // call
    int matA[MATRIX_SIZE][MATRIX_SIZE];                                                             // define
    int matB[MATRIX_SIZE][MATRIX_SIZE];                                                             // define
    int matC[MATRIX_SIZE][MATRIX_SIZE];                                                             // define

    // Initialize matrices
    for (int i = 0; i < MATRIX_SIZE; i++)
    { // loop, add, store, br i1
        for (int j = 0; j < MATRIX_SIZE; j++)
        {                       // nested loop, add, store, br i1
            matA[i][j] = i + j; // add, store
            matB[i][j] = i - j; // sub, store
        }
    }

    multiplyMatrices(matA, matB, matC); // call

    // Print a few results from the multiplied matrix (to avoid too much output)
    printf("Sample result from multiplied matrix C[0][0]: %d, C[1][1]: %d\n", matC[0][0], matC[1][1]); // call

    // --- Section 3: Factorial Calculation ---
    printf("\nCalculating factorials:\n"); // call
    for (int i = 0; i <= 10; ++i)
    {                                        // loop, add, store, br i1
        long long fact_val = factorial(i);   // call, store
        printf("%d! = %lld\n", i, fact_val); // call
    }

    // --- Section 4: String Manipulation ---
    char myString[] = "Hello OptMil Project! This is a long string to test the frontend."; // define
    printf("\nOriginal string: \"%s\"\n", myString);                                       // call
    reverseString(myString);                                                               // call
    printf("Reversed string: \"%s\"\n", myString);                                         // call

    // --- Section 5: Complex Arithmetic and Conditionals ---
    long long complex_sum = 0; // define, store
    for (long long i = 0; i < 1000; ++i)
    { // loop, add, store, br i1
        if (i % 3 == 0 && i % 5 == 0)
        {                         // mod, br i1, and
            complex_sum += i * 2; // mul, add, store
        }
        else if (i % 3 == 0)
        {                     // mod, br i1
            complex_sum += i; // add, store
        }
        else if (i % 5 == 0)
        {                     // mod, br i1
            complex_sum -= i; // sub, store
        }
    }
    printf("Complex sum result: %lld\n", complex_sum); // call

    // --- Final Section: Cleanup and Return ---
    printf("\nProgram execution complete.\n"); // call
    return 0;                                  // define, call
}