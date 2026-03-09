#include <stdio.h>

// f: 01001100001111101100000100000010
// i:         10111110110000010000001000
//            ^                       ^
//            |                       |

#define VAL1 10000
#define VAL2 100000L
#define VAL3 10001

void sum1(int val) {
    float sum = 0.0f, corr = 0.0f;
    for (int i = 1; i <= val; i++) {
        float y = i - corr;
        float t = sum + y;  // may carry or drop
        // NOTE: must minus `sum` first
        corr = (t - sum) - y; // get value that be rounded
        // if (val == VAL1) {
        //     int a = t;
        //     int b = sum;
        //     if ((int)(t - sum) != (a - b)) {
        //         printf("%d: %d\n", i, (int)(t - sum) - (a - b));
        //     }
        // }
        sum = t;
    }

    printf("Sum1 is %f\n", sum);
}

void sum2(int val) {
    float sum = 0.0f;
    for (int i = 1; i <= val; i++) {
        sum += i;
    }

    printf("Sum2 is %f\n", sum);
}

void sum3(float val) {
    printf("Sum3 is %f\n", (1.f + val) / 2.f * val);
}

void sum4(int val) {
    float sum = 0.0f, corr = 0.0f;
    for (int i = 1; i <= val; i++) {
        float y = i - corr;
        float t = sum + y;  // may carry or drop
        // {
        //     int a = t;
        //     int b = y;
        //     if ((int)(t - y) != (a - b)) {
        //         printf("%d: %d\n", i, (int)(t - y) - (a - b));
        //     }
        // }
        corr = (t - y) - sum;  // WRONG!!!
        sum = t;
    }

    printf("Sum4 is %f\n", sum);
}

int main() {
    sum1(VAL1);  // NOTE: works
    sum2(VAL1);
    sum3(VAL1);
    sum4(VAL1);  // 50005004 WRONG!!!
    printf("%d\n", (1 + VAL1) * (VAL1 / 2));
    puts("------------------------------------------------------------");
    sum1(VAL2); // NOTE: does not work
    sum2(VAL2);
    sum3(VAL2);
    printf("%ld\n", (1 + VAL2) * (VAL2 / 2));
    puts("------------------------------------------------------------");
    sum1(VAL3);
    sum2(VAL3);
    sum3(VAL3);
    // i: 10111110110010101100011001
    printf("%d\n", (1 + VAL3) / 2 * VAL3);
    return 0;
}
