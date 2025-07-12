#include <stdio.h>

#define N 64
double A[N][N], B[N][N], C[N][N];

void naive_multiply(double A[N][N], double B[N][N], double C[N][N]) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k)
                C[i][j] += A[i][k] * B[k][j];
        }
}

int main() {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }

    naive_multiply(A, B, C);
    printf("Matrix multiplication complete. Sample: %.2f\n", C[1][1]);
    return 0;
}
