#ifndef __SKIP_LIST_H_
#define __SKIP_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LOG_INFO(fmt, ...) fprintf(stdout,            \
        "\033[32mINFO\033[0m(%s:%d): " fmt "\n",      \
        __func__, __LINE__, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) do {                      \
        fprintf(stderr,                               \
        "\033[31mERROR\033[0m(%s:%d): " fmt "\n",     \
        __func__, __LINE__, ##__VA_ARGS__);           \
        exit(-1);                                     \
        } while (0)

// https://brilliant.org/wiki/skip-lists/

struct list_node {
    struct list_node *prev, *next, *top, *bot;
};

struct sl_node {
    char *key;
    int value;
    struct list_node list;
};

struct sl_head {
    size_t height;  // current height
    size_t num;      // the current number of elements
    struct list_node *first; // always points to the top layer
};


struct sl_head sl_init();
struct sl_head *sl_init_p();
void sl_insert(struct sl_head *head, const char *key, const int value);
bool sl_delete(struct sl_head *head, const char *key);
bool sl_search(const struct sl_head *head, const char *key, int *value);
void sl_erase(struct sl_head *head);
void sl_erase_p(struct sl_head **head);
void sl_pretty_print(const struct sl_head *head);

#endif // __SKIP_LIST_H_
