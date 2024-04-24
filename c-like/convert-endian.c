#include <stdio.h>

static int solution1(int x) {
    return ((x & 0xff) << 24) + (((x >> 8) & 0xff) << 16) + (((x >> 16) & 0xff) << 8) + ((x >> 24) & 0xff);
}

static inline void swap(char *restrict a, char *restrict b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

static int solution2(int x) {
    char *a = (char *)&x;
    swap(a, a + 3);
    swap(a + 1, a + 2);
    return x;
}

int main() {
    int x = 100;
    printf("%d\n", solution1(x));
    printf("%d\n", solution2(x));
    return 0;
}
