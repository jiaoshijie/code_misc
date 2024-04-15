#include <stdio.h>

#define __same_type(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))
#define BUILD_BUG_ON_ZERO(e) ((int)(sizeof(struct { int:(-!!(e)); })))
#define __must_be_array(a)   BUILD_BUG_ON_ZERO(__same_type((a), &(a)[0]))
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]) + __must_be_array(arr))
// #define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

// void func(long int *d) {
//     printf("%ld\n", ARRAY_SIZE(d));
// }

int main() {
    long d[] = {1, 2, 3, 4, 5, 6};
    printf("%ld\n", ARRAY_SIZE(d));
    // func(d);
    printf("%d\n", BUILD_BUG_ON_ZERO(0));
    return 0;
}
