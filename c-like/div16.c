#include <assert.h>
#include <stdint.h>

int div16(int x) {
    return (x >> 4) + (x >> 31 & !!(x & 15));
}

int main() {
    assert(div16(17) == 17/16);
    assert(div16(33) == 33/16);
    assert(div16(-17) == -17/16);
    assert(div16(-33) == -33/16);
    assert(div16(-34) == -34/16);
    assert(div16(-32) == -32/16);
    for (int i = 1; i < INT32_MAX; i++) {
        assert(div16(i) == i / 16);
    }
    for (int i = -1; i > INT32_MIN; i--) {
        assert(div16(i) == i / 16);
    }
    return 0;
}
