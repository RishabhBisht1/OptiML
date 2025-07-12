#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 512

// Randomly initialize matrix
void init_matrix(float matrix[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matrix[i][j] = (float)(rand() % 100) / 10.0f;
}

// Multiply two matrices and store the result
void multiply_matrix(float A[N][N], float B[N][N], float C[N][N]) {
    // Initializing result matrix to zero
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            C[i][j] = 0.0f;

    // Matrix multiplication
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            float r = A[i][k];  // loop-invariant memory access
            for (int j = 0; j < N; j++) {
                C[i][j] += r * B[k][j];
            }
        }
    }
}

// Checksum to verify result (simple, no optimization required)
float checksum(float matrix[N][N]) {
    float sum = 0.0f;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            sum += matrix[i][j];
    return sum;
}

int main() {
    static float A[N][N], B[N][N], C[N][N];

    srand(42);
    init_matrix(A);
    init_matrix(B);

    clock_t start = clock();
    multiply_matrix(A, B, C);
    clock_t end = clock();

    float time_taken = (float)(end - start) / CLOCKS_PER_SEC;
    float sum = checksum(C);

    printf("Matrix multiplication completed.\n");
    printf("Checksum: %.2f\n", sum);
    printf("Time taken: %.4f seconds\n", time_taken);

    return 0;
}
