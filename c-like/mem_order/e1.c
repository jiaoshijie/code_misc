#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <stdatomic.h>

// https://preshing.com/20120515/memory-reordering-caught-in-the-act/
// In particular, each processor is allowed to delay the effect of
// a store past any load from a different location.

sem_t sem1, sem2, end_sem;

int X, Y;
int r1, r2;

void *handler_1(void *args) {
    (void) args;
    srandom(time(NULL));

    for (;;) {
        sem_wait(&sem1);
        while (random() % 8 != 0) {}

        // atomic_store_explicit(&X, 1, memory_order_relaxed);
        atomic_store_explicit(&X, 1, memory_order_release);
        asm volatile("" ::: "memory");  // prevent compiler reordering
        // asm volatile("mfence" ::: "memory");  // prevent reordering, this only works in x86 arch
        // r1 = atomic_load_explicit(&Y, memory_order_relaxed);
        r1 = atomic_load_explicit(&Y, memory_order_acquire);

        sem_post(&end_sem);
    }

    return NULL;
}

void *handler_2(void *args) {
    (void) args;
    srandom(time(NULL));

    for (;;) {
        sem_wait(&sem2);
        while (random() % 8 != 0) {}

        // atomic_store_explicit(&Y, 1, memory_order_relaxed);
        atomic_store_explicit(&Y, 1, memory_order_release);
        asm volatile("" ::: "memory");  // prevent compiler reordering
        // asm volatile("mfence" ::: "memory");  // prevent reordering, this only works in x86 arch
        // r2 = atomic_load_explicit(&X, memory_order_relaxed);
        r2 = atomic_load_explicit(&X, memory_order_acquire);

        sem_post(&end_sem);
    }

    return NULL;
}

int main() {
    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);
    sem_init(&end_sem, 0, 0);

    pthread_t thread_1, thread_2;
    pthread_create(&thread_1, NULL, handler_1, NULL);
    pthread_create(&thread_2, NULL, handler_2, NULL);

    int detected = 0;
    for (int i = 0; ; i++) {
        X = 0;
        Y = 0;

        sem_post(&sem1);
        sem_post(&sem2);

        sem_wait(&end_sem);
        sem_wait(&end_sem);

        if (r1 == 0 && r2 == 0) {
            printf("%d reorders detected after %d iterations\n", ++detected, i);
        }
    }

    return 0;
}
