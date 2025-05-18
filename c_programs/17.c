#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 1024  // Adjust to larger values for more dramatic differences

double **allocate_matrix(int size) {
    double **matrix = malloc(size * sizeof(double *));
    for (int i = 0; i < size; i++) {
        matrix[i] = malloc(size * sizeof(double));
        memset(matrix[i], 0, size * sizeof(double));
    }
    return matrix;
}

void free_matrix(double **matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void fill_matrix(double **matrix, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matrix[i][j] = (double)(rand() % 100);
}

// Naive matrix multiply (i, j, k ordering)
void multiply(double **A, double **B, double **C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            double sum = 0;
            for (int k = 0; k < size; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

double time_diff(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

int main() {
    srand(time(NULL));
    double **A = allocate_matrix(SIZE);
    double **B = allocate_matrix(SIZE);
    double **C = allocate_matrix(SIZE);

    fill_matrix(A, SIZE);
    fill_matrix(B, SIZE);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    multiply(A, B, C, SIZE);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = time_diff(start, end);
    printf("Matrix multiplication completed in %.4f seconds\n", elapsed);

    // Uncomment to verify content, not for large sizes
    // printf("C[0][0] = %f\n", C[0][0]);

    free_matrix(A, SIZE);
    free_matrix(B, SIZE);
    free_matrix(C, SIZE);

    return 0;
}
