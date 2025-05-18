#include <stdio.h>
#include <math.h>

#define N 8

void dct(float input[N][N], float output[N][N]) {
    float ci, cj, dct1, sum;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == 0)
                ci = 1 / sqrt(N);
            else
                ci = sqrt(2) / sqrt(N);
            if (j == 0)
                cj = 1 / sqrt(N);
            else
                cj = sqrt(2) / sqrt(N);

            sum = 0;
            for (int x = 0; x < N; x++) {
                for (int y = 0; y < N; y++) {
                    dct1 = input[x][y] *
                           cos((2 * x + 1) * i * M_PI / (2 * N)) *
                           cos((2 * y + 1) * j * M_PI / (2 * N));
                    sum += dct1;
                }
            }
            output[i][j] = ci * cj * sum;
        }
    }
}

int main() {
    float input[N][N] = {
        {52, 55, 61, 66, 70, 61, 64, 73},
        {63, 59, 55, 90, 109, 85, 69, 72},
        {62, 59, 68, 113, 144, 104, 66, 73},
        {63, 58, 71, 122, 154, 106, 70, 69},
        {67, 61, 68, 104, 126, 88, 68, 70},
        {79, 65, 60, 70, 77, 68, 58, 75},
        {85, 71, 64, 59, 55, 61, 65, 83},
        {87, 79, 69, 68, 65, 76, 78, 94}
    };
    float output[N][N];

    dct(input, output);

    // Print DCT coefficients
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%6.2f ", output[i][j]);
        printf("\n");
    }

    return 0;
}
