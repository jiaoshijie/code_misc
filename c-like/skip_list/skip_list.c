#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "skip_list.h"

// static int ilog2(unsigned long oprand) {
//     return 63 - __builtin_clzl(oprand);
// }

static bool tossing_coin() {
    srand(time(NULL));
    return (bool)(rand() & 0b1);
}

static struct sl_node *get_sl_node(struct list_node *top) {
    struct list_node *t = top;
    while (t->bot) {
        t = t->bot;
    }

    return (struct sl_node *)((size_t)t - (size_t)&(((struct sl_node *)(0))->list));
}

static struct list_node *recursive_insert(struct list_node *head,
        const char *key, const int value, size_t *num) {
    struct list_node *has_layer = NULL, *ret = NULL;

    struct list_node *p = head->next;
    while (p) {
        if (strcmp(get_sl_node(p)->key, key) < 0) {
            if (p->next)
                p = p->next;
            else
                break;
        } else if (strcmp(get_sl_node(p)->key, key) == 0) {
            LOG_INFO("key `%s` has already store in the skip list, so do nothing", key);
            return NULL;
        } else {  // q->key > key --- strcmp() > 0
            p = p->prev;
            break;
        }
    }
    if (!p) p = head;  // NOTE: When there is no element, need this operation

    if (p->bot != NULL) {
        has_layer = recursive_insert(p->bot, key, value, num);

        if (has_layer && tossing_coin()) {
            ret = (struct list_node *)malloc(sizeof(struct list_node));
            if (!ret) {
                LOG_ERROR("new list_node malloc failed, when insert [%s]:[%d]", key, value);
            }
            memset(ret, 0, sizeof(struct list_node));
            ret->bot = has_layer;
            has_layer->top = ret;
        }

    } else {
        struct sl_node *new_sl_node = malloc(sizeof(struct sl_node));
        if (!new_sl_node) {
            LOG_ERROR("new_sl_node malloc failed, when insert [%s]:[%d]", key, value);
        }
        memset(new_sl_node, 0, sizeof(struct sl_node));

        new_sl_node->key = strdup(key);
        if (!new_sl_node->key) {
            LOG_ERROR("strdup failed, when insert [%s]:[%d]", key, value);
        }
        new_sl_node->value = value;
        (*num)++;
        ret = &new_sl_node->list;
    }

    if (ret) {
        ret->next = p->next;
        p->next = ret;
        ret->prev = p;
        if (ret->next) {
            ret->next->prev = ret;
        }
    }

    return ret;
}

void sl_insert(struct sl_head *head, const char *key, const int value) {
    struct list_node *has_layer = recursive_insert(head->first, key, value, &head->num);
    if (has_layer && tossing_coin()) {
        struct list_node *head_layer = malloc(sizeof(struct list_node));
        struct list_node *n_layer = malloc(sizeof(struct list_node));
        if (!n_layer && !head_layer) {
            LOG_ERROR("n_layer or head_layer malloc failed when insert [%s]:[%d]", key, value);
        }
        memset(head_layer, 0, sizeof(struct list_node));
        memset(n_layer, 0, sizeof(struct list_node));

        n_layer->bot = has_layer;
        has_layer->top = n_layer;

        head_layer->next = n_layer;
        n_layer->prev = head_layer;

        head_layer->bot = head->first;
        head->first->top = head_layer;
        head->first = head_layer;

        head->height++;
    }
}

static bool recursive_delete(struct list_node *head, const char *key, bool is_head) {
    if (is_head) {
        if (head->bot != NULL) {
            if (recursive_delete(head->bot, key, true)) {
                struct list_node *p = head->prev, *q = head->next;
                p->next = q;
                if (q)
                    q->prev = p;
                free(head);
                return true;
            }
        } else {
            struct list_node *p = head->prev, *q = head->next;
            struct sl_node *s = get_sl_node(head);
            p->next = q;
            if (q)
                q->prev = p;
            free(s->key);
            free(s);
            return true;
        }
    } else {
        if (head->bot != NULL) {
            struct list_node *it = head->next;
            while (it) {
                if (strcmp(get_sl_node(it)->key, key) < 0) {
                    it = it->next;
                } else if (strcmp(get_sl_node(it)->key, key) == 0) {
                    if (recursive_delete(it->bot, key, true)) {
                        struct list_node *p = it->prev, *q = it->next;
                        p->next = q;
                        if (q)
                            q->prev = p;
                        free(it);
                        return true;
                    }
                } else {
                    it = it->prev;
                    break;
                }
            }
            if (!it) it = head;
            return recursive_delete(it->bot, key, false);
        } else {
            struct list_node *it = head->next;
            while(it) {
                if (strcmp(get_sl_node(it)->key, key) < 0) {
                    it = it->next;
                } else if (strcmp(get_sl_node(it)->key, key) == 0) {
                    struct list_node *p = it->prev, *q = it->next;
                    p->next = q;
                    if (q)
                        q->prev = p;
                    struct sl_node *s = get_sl_node(it);
                    free(s->key);
                    free(s);
                    return true;
                } else {
                    break;
                }
            }
        }
    }
    return false;
}

bool sl_delete(struct sl_head *head, const char *key) {
    if (recursive_delete(head->first, key, false)) {
        head->num--;
        // NOTE: cleanup non-element lists, but keep the last empty list
        struct list_node *top = head->first;
        while (top && top->bot) {
            if (top->next == NULL) {
                head->height--;
                struct list_node *t = top;
                top = top->bot;
                free(t);
            } else {
                break;
            }
        }
        head->first = top;
        // TODO: maybe also cleanup duplicated lists
        return true;
    }
    return false;
}

void sl_erase(struct sl_head *head) {
    struct list_node *top = head->first;
    struct list_node *p = NULL, *t = NULL;
    while (top->bot) {
        p = top->next;
        while (p) {
            t = p;
            p = p->next;
            free(t);
        }
        t = top;
        top = top->bot;
        free(t);
    }

    p = top->next;
    while (p) {
        struct sl_node *s = get_sl_node(p);
        p = p->next;

        free(s->key);
        free(s);
    }
    free(top);

    head->first = NULL;
    head->height = 1;
    head->num = 0;
}

bool sl_search(const struct sl_head *head, const char *key, int *value) {
    struct list_node *p = head->first;

    while (p) {
        p = p->next;
        while (p) {
            if (strcmp(get_sl_node(p)->key, key) < 0) {
                p = p->next;
            } else if (strcmp(get_sl_node(p)->key, key) == 0) {
                *value = get_sl_node(p)->value;
                return true;
            } else {  // strcmp(get_sl_node(p)->key, key) > 0
                p = p->prev->bot;
                break;
            }
        }
    }
    return false;
}

void sl_pretty_print(const struct sl_head *head) {
    struct list_node *top = head->first;
    printf("\n------------------sl begin--------------------\n");
    printf("height: %ld, num: %ld\n", head->height, head->num);
    while (top) {
        struct list_node *p = top->next;
        printf("HEAD->");
        while (p) {
            struct sl_node *s = get_sl_node(p);
            printf("|[%s]:[%x]|->", s->key, s->value);
            p = p->next;
        }
        printf("NULL\n");

        top = top->bot;
    }
    printf("-------------------sl end---------------------\n\n");
}

struct sl_head sl_init() {
    struct sl_head ret = {
        .height = 1,
        .num = 0,
        .first = (struct list_node *)malloc(sizeof(struct list_node)),
    };
    if (!ret.first) {
        LOG_ERROR("malloc head->first failed");
    }
    memset(ret.first, 0, sizeof(struct list_node));

    return ret;
}

struct sl_head *sl_init_p() {
    struct sl_head *ret = malloc(sizeof(struct sl_head));
    if (!ret) {
        LOG_ERROR("ret malloc failed");
    }
    struct sl_head elem = sl_init();
    memcpy(ret, &elem, sizeof(struct sl_head));
    return ret;
}

void sl_erase_p(struct sl_head **head) {
    sl_erase(*head);
    free(*head);
    *head = NULL;
}
