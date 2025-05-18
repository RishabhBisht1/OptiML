#include <stdio.h>
#include <time.h>

#define SIZE 1000000

int main() {
    clock_t start, end;
    double sum = 0.0;

    start = clock();
    for (int i = 1; i < SIZE; i++) {
        sum += i * 0.5;
    }
    end = clock();

    printf("Sum: %f\n", sum);
    printf("Time taken: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}