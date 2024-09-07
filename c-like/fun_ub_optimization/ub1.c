// https://www.reddit.com/r/cpp/comments/1cct7me/fun_example_of_unexpected_ub_optimization/

#include <stdio.h>

static void (*fptr)();

static void func() {
    printf("function\n");
}

void never_called() {
    fptr = &func;
}

int main() {
    fptr();
    return 0;
}
