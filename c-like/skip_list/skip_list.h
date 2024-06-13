#ifndef __SKIP_LIST_H_
#define __SKIP_LIST_H_

// https://brilliant.org/wiki/skip-lists/

struct list_node {
    struct list_node **pprev, *next, *top, *bot;
};

struct sl_node {
    char *key;
    int value;
    struct list_node list;
};

struct sl_head {
    size_t cheight;  // current height
    size_t len;      // the current number of elements
    struct list_node *first; // always points to the top layer
};

#define SL_HEAD_INIT {0, 0, 0}
#define LIST_NODE_INIT {0, 0, 0, 0}
#define SL_NODE_INIT {0, 0, 0}

void sl_insert(struct sl_head *head, const char *key, const int value);
int sl_delete(struct sl_head *head, const char *key);
int sl_search(struct sl_head *head, const char *key);

#endif // __SKIP_LIST_H_
