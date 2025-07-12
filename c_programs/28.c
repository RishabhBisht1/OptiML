#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define N 10000
uint32_t arr[N], tmp[N];

void radix_sort(uint32_t *arr, uint32_t *tmp, int N) {
    const int BITS = 8;
    const int BUCKETS = 1 << BITS;
    uint32_t *from = arr, *to = tmp;

    for (int shift = 0; shift < 32; shift += BITS) {
        int count[BUCKETS] = {0};

        for (int i = 0; i < N; ++i)
            count[(from[i] >> shift) & (BUCKETS - 1)]++;

        for (int i = 1; i < BUCKETS; ++i)
            count[i] += count[i - 1];

        for (int i = N - 1; i >= 0; --i)
            to[--count[(from[i] >> shift) & (BUCKETS - 1)]] = from[i];

        uint32_t *tmp_ptr = from; from = to; to = tmp_ptr;
    }

    if (from != arr)
        for (int i = 0; i < N; ++i) arr[i] = from[i];
}

int main() {
    for (int i = 0; i < N; ++i) arr[i] = rand();
    radix_sort(arr, tmp, N);
    printf("Radix sort complete. Sample: %u\n", arr[100]);
    return 0;
}
