#include <stdio.h>
#include <assert.h>

int div16(int x) {
    return (x + (x >> 31 & 0x1)) >> 4;
}

int main() {
    assert(div16(17) == 17/16);
    assert(div16(33) == 33/16);
    assert(div16(-17) == -17/16);
    assert(div16(-33) == -33/16);
    return 0;
}
