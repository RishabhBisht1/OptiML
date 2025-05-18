#include <stdio.h>
#include <stdlib.h>

#define SIZE 100000000

int main() {
    int *arr = malloc(sizeof(int) * SIZE);
    if (!arr) return 1;

    // Initialize array
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i % 100;
    }

    long long sum = 0;
    // Sum elements
    for (int i = 0; i < SIZE; i++) {
        sum += arr[i];
    }

    printf("Sum = %lld\n", sum);

    free(arr);
    return 0;
}
