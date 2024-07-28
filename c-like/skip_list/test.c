#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "skip_list.h"

void test1() {
    struct sl_head head = sl_init();
    // char buf[32] = {0};
    // srand(time(0));
    // for (int i = 0; i < 100; i++) {
    //     int number = rand() % ('z' + 1);
    //     if ((number >= 'a' && number <= 'z') || (number >= 'A' && number <= 'Z')) {
    //         sprintf(buf, "%c", number);
    //         sl_insert(&head, buf, number);
    //     }
    // }
    sl_insert(&head, "b", 0xb);
    sl_insert(&head, "a", 0xa);
    sl_insert(&head, "c", 0xc);
    sl_pretty_print(&head);
    int value;
    if (sl_search(&head, "b", &value)) {
        LOG_INFO("b: %x", value);
    }
    if (sl_delete(&head, "b")) {
        LOG_INFO("delete key `b` successfully!!!");
    }
    if (sl_search(&head, "b", &value)) {
        LOG_INFO("b: %x", value);
    } else {
        LOG_INFO("NOT FOUND key `b`");
    }
    sl_pretty_print(&head);
    if (sl_delete(&head, "c")) {
        LOG_INFO("delete key `c` successfully!!!");
    }
    sl_pretty_print(&head);

    if (sl_delete(&head, "a")) {
        LOG_INFO("delete key `a` successfully!!!");
    }
    sl_pretty_print(&head);

    sl_erase(&head);
}

void test2() {
    struct sl_head *head = sl_init_p();

    sl_insert(head, "b", 0xb);
    sl_insert(head, "a", 0xa);
    sl_insert(head, "c", 0xc);
    sl_pretty_print(head);
    int value;
    if (sl_search(head, "b", &value)) {
        LOG_INFO("b: %x", value);
    }
    if (sl_delete(head, "b")) {
        LOG_INFO("delete key `b` successfully!!!");
    }
    if (sl_search(head, "b", &value)) {
        LOG_INFO("b: %x", value);
    } else {
        LOG_INFO("NOT FOUND key `b`");
    }
    sl_pretty_print(head);
    if (sl_delete(head, "c")) {
        LOG_INFO("delete key `c` successfully!!!");
    }
    sl_pretty_print(head);

    if (sl_delete(head, "a")) {
        LOG_INFO("delete key `a` successfully!!!");
    }
    sl_pretty_print(head);

    sl_erase_p(&head);
}

int main() {
    test1();
    printf("**********************************************\n");
    test2();
    return 0;
}
