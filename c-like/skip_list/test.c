#include <stdio.h>

#include "skip_list.h"


int main() {
    struct sl_head head = SL_HEAD_INIT;
    printf("%ld\n", head.len);
    return 0;
}
