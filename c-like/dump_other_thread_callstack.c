#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <signal.h>
#include <execinfo.h>

/*
 * gcc dump_other_thread_callstack.c -rdynamic -o out
 * */

#define BT_BUF_SIZE 20
int g_b = 0;

void report_error(const char* msg) {
    assert(msg != NULL);
    perror(msg);
    exit(1);
}

void a1() {
    while (1) {
        sleep(2);
        printf("a\n");
    }
}

void a2() {
    a1();
}

void a3() {
    a2();
}

void b1() {
    while (1) {
        // sleep(3);
        // printf("b\n");
        g_b += 1;
    }
}

void b2() {
    b1();
}

void *a_handler(void *arg) {
    (void) arg;

    a3();

    return NULL;
}

void *b_handler(void *arg) {
    (void) arg;

    b2();

    return NULL;
}

void sig_user2_handler(int sig_num) {
    int nptrs;
    void *buffer[BT_BUF_SIZE];
    char **strings;

    nptrs = backtrace(buffer, BT_BUF_SIZE);
    printf("backtrace() returned %d addresses\n", nptrs);

    /* The call backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO)
       would produce similar output to the following: */

    strings = backtrace_symbols(buffer, nptrs);
    if (strings == NULL) {
        perror("backtrace_symbols");
        exit(EXIT_FAILURE);
    }

    for (size_t j = 0; j < nptrs; j++)
        printf("%s\n", strings[j]);

    free(strings);
}

int main() {
    pthread_t a, b;

    printf("pid: %d\n", getpid());

    if (signal(SIGUSR2, sig_user2_handler) == SIG_ERR) {
        report_error("register SIGUSR2 signal failed");
    }

    if (pthread_create(&a, NULL, a_handler, NULL) != 0) {
        report_error("pthread_create a failed");
    }

    if (pthread_create(&b, NULL, b_handler, NULL) != 0) {
        report_error("pthread_create b failed");
    }

    while (1) {
        sleep(10);
        printf("main\n");
    }

    return 0;
}
