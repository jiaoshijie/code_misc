#include "skip_list.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int ilog2(unsigned long oprand) {
    return 63 - __builtin_clzl(oprand);
}

bool tossing_coin() {
    srand(time(NULL));
    return rand() & 1;
}

static struct list_node **search(struct sl_head *head, const char *key) {
    if (!head->link) {
        assert(head->len == 0 && "ERROR: head->link == NULL but head->len != 0!!!");
        return &head->link;
    }
}

static void create_new_layer(struct sl_head *head) {
    struct list_node *t = head->link, *p, *q;

    struct list_node *top_head = malloc(sizeof(struct list_node));
    assert(top_head && "create_new_layer failed");
    memset(top_head, 0, sizeof(struct list_node));

    head->link = top_head;
    top_head->pprev = &head->link;
    top_head->bot = t;
    t->pprev = &top_head->bot;
    t->top = head->link;

    q = head->link;
    p = t;
    while (p->next) {
        if (tossing_coin()) {
            struct list_node *top_node = malloc(sizeof(struct list_node));
            assert(top_node && "create_new_layer failed");
            memset(top_node, 0, sizeof(struct list_node));

            t = p;
            

        }
        p = p->next;
    }
}

void sl_insert(struct sl_head *head, const char *key, const int value) {
    struct list_node **pos = search(head, key);

    struct sl_node *new_node = malloc(sizeof(struct sl_node));
    memset(new_node, 0, sizeof(struct sl_node));

    new_node->key = strdup(key);
    assert(new_node->key && "sl_insert failed, because new_node->key is null.");
    new_node->value = value;
    new_node->link = malloc(sizeof(struct struct list_node));
    assert(new_node->link && "sl_insert filed, becasue new_node->link is null");

    
}

int sl_delete(struct sl_head *head, const char *key) {
}

int sl_search(struct sl_head *head, const char *key) {
}
