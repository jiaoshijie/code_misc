#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdint.h>
#include <assert.h>

#define THREAD_NUM 10
#define COUNT_TIME_PER_THREAD 500

#define LOCKED true
#define UNLOCKED false

typedef struct {
    bool locked;
} my_mutex_t;

uint64_t g_count = 0;
my_mutex_t g_mutex;

// This function should only be called once
void my_mutex_init(my_mutex_t *m) {
    m->locked = UNLOCKED;
}

void with_lock(my_mutex_t *m) {
    // spinlock
#if 0
    while (atomic_load_explicit(&m->locked, memory_order_relaxed) != UNLOCKED) {}
    atomic_store_explicit(&m->locked, LOCKED, memory_order_relaxed);
#endif

#if 1
    bool unlocked = UNLOCKED;
    while (!atomic_compare_exchange_weak_explicit(&m->locked, &unlocked, LOCKED,
                memory_order_relaxed, memory_order_relaxed)) {
        unlocked = UNLOCKED;
        // In the internal loop using atomic_load_explicit,
        // because atomic_compare_exchange_weak_explicit is expensive
        while (atomic_load_explicit(&m->locked, memory_order_relaxed) == LOCKED) {}
    }
#endif

#if 0
    bool unlocked = UNLOCKED;
    while (!atomic_compare_exchange_weak(&m->locked, &unlocked, LOCKED)) {
        unlocked = UNLOCKED;
        // In the internal loop using atomic_load_explicit,
        // because atomic_compare_exchange_weak_explicit is expensive
        while (atomic_load(&m->locked) == LOCKED) {}
    }
#endif

    g_count++;

#if 1
    atomic_store_explicit(&m->locked, UNLOCKED, memory_order_relaxed);
#endif

#if 0
    atomic_store(&m->locked, UNLOCKED);
#endif

}

void *thread_handler(void *arg) {
    (void) arg;
    for (int i = 0; i < COUNT_TIME_PER_THREAD; i++) {
        with_lock(&g_mutex);
    }
    return NULL;
}

int main() {
    my_mutex_init(&g_mutex);
    pthread_t th_pool[THREAD_NUM] = { 0 };
    size_t iter_num = 0;

    for (;; iter_num++) {
        for (int i = 0; i < THREAD_NUM; i++) {
            pthread_create(&th_pool[i], NULL, thread_handler, NULL);
        }

        for (int i = 0; i < THREAD_NUM; i++) {
            pthread_join(th_pool[i], NULL);
        }

        // assert(g_count == THREAD_NUM * COUNT_TIME_PER_THREAD);
        if (g_count != THREAD_NUM * COUNT_TIME_PER_THREAD) {
            printf("iter: %lu, count: %lu\n", iter_num, g_count);
        }
        g_count = 0;
    }

    return 0;
}
