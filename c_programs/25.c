#include <stdio.h>
#include <stdint.h>

#define PIXELS 1000
uint8_t rgba[PIXELS * 4];
uint8_t gray[PIXELS];

void rgba_to_gray(uint8_t *rgba, uint8_t *gray, size_t px) {
    for (size_t i = 0; i < px; ++i) {
        uint32_t p = ((uint32_t*)rgba)[i];
        uint8_t r = p & 0xFF, g = (p>>8)&0xFF, b = (p>>16)&0xFF;
        gray[i] = (77*r + 150*g + 29*b) >> 8;
    }
}

int main() {
    for (int i = 0; i < PIXELS * 4; ++i)
        rgba[i] = i % 256;

    rgba_to_gray(rgba, gray, PIXELS);
    printf("Grayscale conversion complete. Sample: %u\n", gray[10]);
    return 0;
}
