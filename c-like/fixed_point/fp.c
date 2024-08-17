#include "fp.h"
#include <assert.h>

fixed_t from_float(float num) {
    return (fixed_t)(num * (1 << FRACTIONAL_LEN));
}

float to_float(fixed_t num) {
    return (float)(num) / (1 << FRACTIONAL_LEN);
}

fixed_t fixed_add(fixed_t a, fixed_t b) {
    return a + b;
}

fixed_t fixed_sub(fixed_t a, fixed_t b) {
    return a - b;
}

fixed_t fixed_mul(fixed_t a, fixed_t b) {
    // TODO: The rounding now it round-down
    // Change it to round-to-even Maybe
    // round-to-even in binary format means let the least significant bit be 0
    // 0b01.10  ->  0b10
    // 0b00.10  ->  0b00
    return (fixed_t)(((l_fixed_t)a * (l_fixed_t)b) >> FRACTIONAL_LEN);
}

fixed_t fixed_div(fixed_t dividend, fixed_t divisor) {
    assert(divisor != 0 && "divisor can not be zero!!!");

    return (fixed_t)((((l_fixed_t)dividend) << FRACTIONAL_LEN) / divisor);
}

fixed_t fixed_ceil(fixed_t a) {
    if (!(a & FRACTIONAL_MASK)) {
        return a;
    }
    return fixed_add(a, ONE) & INTEGER_MASK;
}

fixed_t fixed_floor(fixed_t a) {
    if (!(a & FRACTIONAL_MASK)) {
        return a;
    }

    return a & INTEGER_MASK;
}

fixed_t fixed_round(fixed_t a) {
    // if (!(a & FRACTIONAL_MASK)) {
    //     return a;
    // }

    if (IS_NEG(a)) {
        return fixed_ceil(a);
    }
    return fixed_floor(a);
}
