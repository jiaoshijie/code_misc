#ifndef __JSJ_FIXED_POINT_
#define __JSJ_FIXED_POINT_

#include <stdint.h>

typedef int32_t fixed_t;  // fixed point
typedef int64_t l_fixed_t;  // NOTE: for multiply and division operation
#define FRACTIONAL_LEN 6  // fractional part length

#define INTEGER_LEN         (sizeof(fixed_t) * 8 - FRACTIONAL_LEN)
#define IS_NEG(x)           (!!(x & (1 << (sizeof(fixed_t) * 8  - 1))))
#define ONE                 ((fixed_t)1 << FRACTIONAL_LEN)
#define FIXED(x)            ((fixed_t)x << FRACTIONAL_LEN)
#define FRACTIONAL_MASK     (ONE - 1)
#define INTEGER_MASK        ((fixed_t)-1 ^ FRACTIONAL_MASK)
#define TO_INTEGER(x)       (x >> FRACTIONAL_LEN)

fixed_t from_float(float num);
float to_float(fixed_t num);

fixed_t fixed_add(fixed_t a, fixed_t b);
fixed_t fixed_sub(fixed_t a, fixed_t b);
fixed_t fixed_mul(fixed_t a, fixed_t b);
fixed_t fixed_div(fixed_t dividend, fixed_t divisor);

fixed_t fixed_ceil(fixed_t a);
fixed_t fixed_floor(fixed_t a);
fixed_t fixed_round(fixed_t a);

#endif  // __JSJ_FIXED_POINT_
