#include <assert.h>
#include <stdint.h>
#include <stdio.h>

// NOTE: This behave is defined in IEEE 754 standard,
// and C standard adopt the behave from IEEE 754

int main() {
    float f1 = 0.0f, f2 = -0.0f, _1f1 = 1 / f1, _1f2 = 1 / f2;
    uint32_t i1 = *(uint32_t *)&f1, i2 = *(uint32_t *)&f2;
    printf("i1 = 0x%08x, i2 = 0x%08x\n", i1, i2);
    printf("_1f1 = 0x%08x, _1f2 = 0x%08x\n", *(uint32_t *)&_1f1, *(uint32_t *)&_1f2);
    assert(f1 == f2);
    // assert(i1 == i2);
    assert(_1f1 == _1f1);
    assert(_1f2 == _1f2);
    assert(_1f1 == _1f2);
    return 0;
}
