#include <stdio.h>
#include <math.h>

#define W 64
#define H 64
#define W2 32
#define H2 32

double src[W * H], dst[W2 * H2];

int clamp(int x, int lo, int hi) {
    if (x < lo) return lo;
    if (x > hi) return hi;
    return x;
}

double lanczos(double x, int a) {
    if (x == 0.0) return 1.0;
    if (x < -a || x > a) return 0.0;
    double pix = M_PI * x;
    return a * sin(pix) * sin(pix / a) / (pix * pix);
}

void resample(double *src, int w, int h, double *dst, int w2, int h2, int a) {
    for (int y2 = 0; y2 < h2; ++y2)
        for (int x2 = 0; x2 < w2; ++x2) {
            double x = (x2 + 0.5) * w / w2 - 0.5;
            double y = (y2 + 0.5) * h / h2 - 0.5;
            double sum=0, norm=0;
            for (int dy = -a+1; dy < a; dy++)
                for (int dx = -a+1; dx < a; dx++) {
                    int xx = clamp((int)floor(x)+dx, 0, w-1);
                    int yy = clamp((int)floor(y)+dy, 0, h-1);
                    double wgt = lanczos(x - xx, a) * lanczos(y - yy, a);
                    sum += src[yy*w+xx] * wgt;
                    norm += wgt;
                }
            dst[y2*w2+x2] = sum / norm;
        }
}

int main() {
    for (int i = 0; i < W * H; ++i)
        src[i] = i % 256;

    resample(src, W, H, dst, W2, H2, 3);
    printf("Resampling done. Sample: %.2f\n", dst[10]);
    return 0;
}
