#include <stdio.h>
#include <string.h>

#define WINDOW_SIZE 20
#define LOOKAHEAD_BUFFER_SIZE 15

void lz77_compress(const char* input) {
    int i = 0;
    int len = strlen(input);

    while (i < len) {
        int match_length = 0;
        int match_distance = 0;

        for (int j = i - 1; j >= 0 && i - j <= WINDOW_SIZE; j--) {
            int k = 0;
            while (input[j + k] == input[i + k] && k < LOOKAHEAD_BUFFER_SIZE && i + k < len)
                k++;
            if (k > match_length) {
                match_length = k;
                match_distance = i - j;
            }
        }

        if (match_length >= 3) {
            printf("<%d,%d,%c>", match_distance, match_length, input[i + match_length]);
            i += match_length + 1;
        } else {
            printf("<0,0,%c>", input[i]);
            i++;
        }
    }
    printf("\n");
}

int main() {
    const char* data = "ABABCABABCD";
    lz77_compress(data);
    return 0;
}
