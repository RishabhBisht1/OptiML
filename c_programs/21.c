#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846
#define N 1024
double real[N], imag[N];

void fft(double *real, double *imag, int n) {
    int i, j = 0;
    for (i = 1; i < n; i++) {
        int bit = n >> 1;
        while (j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;
        if (i < j) {
            double tr = real[i], ti = imag[i];
            real[i] = real[j]; imag[i] = imag[j];
            real[j] = tr;      imag[j] = ti;
        }
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len;
        double wlen_r = cos(ang), wlen_i = sin(ang);
        for (i = 0; i < n; i += len) {
            double ur = 1.0, ui = 0.0;
            for (j = 0; j < len / 2; j++) {
                int u = i + j, v = i + j + len/2;
                double vr = real[v]*ur - imag[v]*ui;
                double vi = real[v]*ui + imag[v]*ur;
                real[v] = real[u] - vr; imag[v] = imag[u] - vi;
                real[u] += vr; imag[u] += vi;
                double ur2 = ur*wlen_r - ui*wlen_i;
                ui = ur*wlen_i + ui*wlen_r;
                ur = ur2;
            }
        }
    }
}

int main() {
    for (int i = 0; i < N; ++i) {
        real[i] = sin(i * 0.01);
        imag[i] = 0.0;
    }
    fft(real, imag, N);
    printf("FFT completed. Sample Output: %.5f + %.5fi\n", real[1], imag[1]);
    return 0;
}
