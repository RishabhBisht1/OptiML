#include <stdio.h>
#define N 100000
double input[N], output[N];

void iir_filter(double *in, double *out, int N, double b0, double b1, double b2, double a1, double a2) {
    double x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    for (int i = 0; i < N; ++i) {
        double x0 = in[i];
        double y0 = b0 * x0 + b1 * x1 + b2 * x2 - a1 * y1 - a2 * y2;
        out[i] = y0;
        x2 = x1; x1 = x0;
        y2 = y1; y1 = y0;
    }
}

int main() {
    for (int i = 0; i < N; ++i)
        input[i] = (i % 100) / 100.0;

    iir_filter(input, output, N, 0.2929, 0.5858, 0.2929, -0.0000, 0.1716);
    printf("IIR filter completed. Output sample: %.4f\n", output[N-1]);
    return 0;
}
