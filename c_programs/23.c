#include <stdio.h>
#include <stdint.h>

unsigned popcount64(uint64_t x) {
    x -= (x >> 1) & 0x5555555555555555ULL;
    x = (x & 0x3333333333333333ULL) + ((x >> 2) & 0x3333333333333333ULL);
    x = (x + (x >> 4)) & 0x0F0F0F0F0F0F0F0FULL;
    return (x * 0x0101010101010101ULL) >> 56;
}

int main() {
    uint64_t value = 0xF0F0F0F0F0F0F0F0ULL;
    unsigned result = popcount64(value);
    printf("Popcount: %u\n", result);
    return 0;
}
