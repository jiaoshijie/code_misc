#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

uint16_t func_condition_op(bool is_real, double f, uint64_t i) {
    uint16_t a;

    // 1. first convert i to double, because double has higher rank than integer
    // 2. then evaluate this expression

    // But Convert uint64_t to double is more complex
    // On x86 architecture, there is no such instruction for converting uint64_t to double
    // So when doing this, the compiler takes some steps:
    //    1. check the MSB (most significant bit) is set or not
    //    2. if it is not set, simply using `cvtsi2sdq` instruction is okj
    //    3. if it is set
    //       3.1         first, right shift i by 1, `(i >> 1)`, this opertion makes (i >> 1) is less then INT64_MAX, so can using `cvtsi2sdq` instruction
    //       3.2         sencod, `((i >> 1) | i && 1)`  NOTE: here is intresting, i don't quite know why
    //       3.3         `double((i >> 1) | i && 1)`
    //       3.4         `2 * double((i >> 1) | i && 1)`
    a = is_real ? f : i;  // this is expression

    // NOTE: I think the convert step should be
    // 1.       i >> 1
    // 2.       double(i >> 1)
    // 3.       2 * double(i >> 1)
    // 4.       2 * double(i >> 1) + (i & 1)

    return a;
}

uint16_t func_condition_if(bool is_real, double f, uint64_t i) {
    uint16_t a;

    if (is_real) {  // this is statement
        a = f;
    } else {
        a = i;
    }

    return a;
}

uint16_t func_condition_op_signed(bool is_real, double f, int64_t i) {
    uint16_t a;

    // 1. first convert i to double, because double has higher rank than integer
    // 2. then evaluate this expression
    // Because `int64_t` to `double` conversion may lose precision, so the result may not correct
    // NOTE: Covert singed int64_t to double is straightforward just using `cvtsi2sdq` instruction
    a = is_real ? f : i;  // this is expression

    return a;
}

uint16_t func_condition_if_signed(bool is_real, double f, int64_t i) {
    uint16_t a;

    if (is_real) {  // this is statement
        a = f;
    } else {
        a = i;
    }

    return a;
}

int main() {
    uint64_t a = 0x3fffffffffffff;
    int64_t b = 0x3fffffffffffff;
    printf("main::a %llu == 0x%llx\n", a, a);
    printf("main::b %llu == 0x%llx\n", b, b);

    // unsigned
    puts("--------------------------------------------------------------------\n");
    printf("func_condition_op(false, 123., a)   = %d\n", func_condition_op(false, 123., a));
    printf("func_condition_if(false, 123., a)   = %d\n", func_condition_if(false, 123., a));

    // why the value is 0 here on x86, but on arm is -1
    // convert double to integer istruction behavior is different on the two architectures, when convert double value that is out of range the target integer value
    //
    // on x86
    //      large positive double value will be the most `negative` number representable in the destination integer
    //      large negative double value will be the most negative number representable in the destination integer
    // on arm
    //      large positive double value will be the most `positive` number representable in the destination integer
    //      large negative double value will be the most negative number representable in the destination integer
    //
    // As the -22 will first be casted to uint64_t
    // then convert to double (which is a positive double value)
    // then convert to int32
    //    on x86 0x80000000
    //    on arm 0x7fffffff
    // then cast to int16/uint16
    //    when casting high precision integer to low precision integer, the c compiler will just truncate the high precision integer
    //    on x86 int16/uint16 = 0x0000 = 0
    //    on arm int16/uint16 = 0xffff = -1
    printf("func_condition_op(false, 123., -22) = %d\n", (int16_t)func_condition_op(false, 123., -22));  // not correct

    printf("func_condition_if(false, 123., -22) = %d\n", (int16_t)func_condition_if(false, 123., -22));

    // signed
    puts("--------------------------------------------------------------------\n");
    printf("func_condition_op_signed(false, 123., b)   = %d\n", func_condition_op_signed(false, 123., a));
    printf("func_condition_if_signed(false, 123., b)   = %d\n", func_condition_if_signed(false, 123., a));
    printf("func_condition_op_signed(false, 123., -22) = %d\n", (int16_t)func_condition_op_signed(false, 123., -22));  // correct
    printf("func_condition_if_signed(false, 123., -22) = %d\n", (int16_t)func_condition_if_signed(false, 123., -22));

    return 0;
}
