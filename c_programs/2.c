#include <stdio.h>
int main() {
    int sum = 0;
    for (int i = 0; i < 10000; ++i)
        sum += i;
    printf("%d\n", sum);
    return 0;
}
