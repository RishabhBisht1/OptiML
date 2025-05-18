#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void sieve(int n) {
    bool* prime = (bool*)malloc((n + 1) * sizeof(bool));
    for (int i = 0; i <= n; i++)
        prime[i] = true;

    for (int p = 2; p * p <= n; p++) {
        if (prime[p]) {
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }

    for (int i = 2; i <= n; i++)
        if (prime[i])
            printf("%d ", i);
    printf("\n");

    free(prime);
}

int main() {
    int n = 100;
    sieve(n);
    return 0;
}
