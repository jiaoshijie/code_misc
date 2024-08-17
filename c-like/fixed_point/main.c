#include <stdio.h>

#include "fp.h"

int main() {
    fixed_t a = from_float(3.625);
    fixed_t b = from_float(2.25);

    printf("%d\n", a);
    printf("%f\n", to_float(a));

    printf("%d\n", b);
    printf("%f\n", to_float(b));

    fixed_t c = fixed_add(a, b);

    printf("%d\n", c);
    printf("%f\n", to_float(c));

    fixed_t d = fixed_sub(a, b);

    printf("%d\n", d);
    printf("%f\n", to_float(d));

    fixed_t e = fixed_sub(b, a);
    printf("%d\n", e);
    printf("%f\n", to_float(e));

    fixed_t f = fixed_add(e, from_float(1.0));
    printf("%d\n", f);
    printf("%f\n", to_float(f));

    fixed_t g = fixed_mul(a, b);
    printf("%d\n", g);  // 522
    printf("%f\n", to_float(g));

    fixed_t h = fixed_div(from_float(8.125), from_float(2.5));
    printf("%d\n", h);  // 208
    printf("%f\n", to_float(h));

    printf("%d\n", TO_INTEGER(fixed_ceil(a)));
    printf("%d\n", TO_INTEGER(fixed_ceil(-a)));
    printf("%d\n", TO_INTEGER(fixed_ceil(FIXED(3))));

    printf("%d\n", TO_INTEGER(fixed_floor(a)));
    printf("%d\n", TO_INTEGER(fixed_floor(-a)));
    printf("%d\n", TO_INTEGER(fixed_floor(FIXED(3))));

    printf("%d\n", TO_INTEGER(fixed_round(a)));
    printf("%d\n", TO_INTEGER(fixed_round(-a)));
    printf("%d\n", TO_INTEGER(fixed_round(FIXED(3))));

    return 0;
}
