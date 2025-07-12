#include <stdio.h>

#define N 1000000
double a[N], b[N], c[N];

void stream_triad(double *a, double *b, double *c, double alpha) {
    for (int i = 0; i < N; ++i)
        a[i] = b[i] + alpha * c[i];
}

int main() {
    for (int i = 0; i < N; ++i) {
        b[i] = i;
        c[i] = i * 2;
    }
    stream_triad(a, b, c, 0.5);
    printf("STREAM Triad done. Sample: %.2f\n", a[100]);
    return 0;
}
