#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>

// NOTE: this example is not wrong, but this code produce the problem.

int z;
bool x;
bool y;

void *handler1(void *arg) {
    (void) arg;

    x = true;

    return NULL;
}

void *handler2(void *arg) {
    (void) arg;

    y = true;

    return NULL;
}

void *handler3(void *arg) {
    (void) arg;

    while (!x) {
    }
    if (y) {
        z++;
    }

    return NULL;
}

void *handler4(void *arg) {
    (void) arg;

    while (!y) {
    }
    if (x) {
        z++;
    }

    return NULL;
}

int main() {
    int iter = 0;
    pthread_t th[4] = {0};

    for (;; iter++) {
        z = 0;
        x = false;
        y = false;

        pthread_create(&th[2], NULL, handler3, NULL);
        pthread_create(&th[3], NULL, handler4, NULL);
        pthread_create(&th[0], NULL, handler1, NULL);
        pthread_create(&th[1], NULL, handler2, NULL);

        pthread_join(th[0], NULL);
        pthread_join(th[1], NULL);
        pthread_join(th[2], NULL);
        pthread_join(th[3], NULL);

        if (z == 0) {
            printf("iter: %d, some weird thing happened\n", iter);
        }

        assert(z != 0);
    }

    return 0;
}
