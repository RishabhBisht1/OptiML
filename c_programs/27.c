#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Block {
    struct Block *next;
    size_t size;
} Block;

static Block *free_list = NULL;

void *pool_alloc(size_t size) {
    size = (size + 7) & ~7;
    Block **prev = &free_list, *curr;
    for (curr = free_list; curr; curr = curr->next) {
        if (curr->size >= size) {
            *prev = curr->next;
            return (void*)(curr+1);
        }
        prev = &curr->next;
    }
    Block *b = sbrk(size + sizeof(Block));
    b->size = size;
    return (void*)(b+1);
}

void pool_free(void *p) {
    Block *b = (Block*)p - 1;
    b->next = free_list;
    free_list = b;
}

int main() {
    int *arr = (int*)pool_alloc(sizeof(int) * 100);
    for (int i = 0; i < 100; ++i) arr[i] = i;
    printf("Memory pool allocation test: %d\n", arr[50]);
    pool_free(arr);
    return 0;
}
