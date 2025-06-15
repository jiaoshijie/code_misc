#include <stdio.h>

// TODO(jiaoshijie): Think about why

void sum1() {
    float sum = 0.0f, corr = 0.0f;
    for (int i = 1; i <= 10000; i++) {
        float y = i - corr;
        float t = sum + y;
        corr = (t - sum) - y;
        sum = t;
    }

    printf("Sum1 is %f\n", sum);
}

void sum2() {
    float sum = 0.0f;
    for (int i = 1; i <= 10000; i++) {
        sum += i;
    }

    printf("Sum2 is %f\n", sum);
}

int main() {
    sum1();
    sum2();
    return 0;
}
