#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sched.h>
#include <pthread.h>

// every 1ms the timer will be expired
#define TIMER_EXPIRE_TIME_US 1 * 1000 * 1000
#define SIG SIGRTMIN
#define USED_CLOCK CLOCK_MONOTONIC

pthread_t main_tid;

// static void sig_handler(int sig, siginfo_t *si, void *uc) {
//     (void) uc;
//
//     timer_t *tinfo = si->si_value.sival_ptr;
//     int or = timer_getoverrun(*tinfo);
//     if (pthread_self() != main_tid)
//         printf("thread_id %x\n", pthread_self());
//     if (or != 0)
//         printf("caught signal %d, overrun: %d\n", sig, or);
// }

static void *thread_handler(void *arg) {
    (void) arg;
    timer_t timerid;

    printf("user created thread_id %x\n", pthread_self());

    struct sched_param param = {};
    param.sched_priority = sched_get_priority_max(SCHED_FIFO);

    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
        perror("Failed to set scheduler:");
        exit(1);
    }

    // struct sigaction sa = {
    //     .sa_flags = SA_SIGINFO,
    //     .sa_sigaction = sig_handler,
    // };
    // sigemptyset(&sa.sa_mask);
    // if (sigaction(SIG, &sa, NULL) == -1) {
    //     perror("Failed to sigaction:");
    //     exit(1);
    // }

    struct sigevent sev = {
        .sigev_notify = SIGEV_SIGNAL,
        .sigev_signo = SIG,
        .sigev_value = {
            .sival_ptr = &timerid,
        },
    };

    if (timer_create(USED_CLOCK, &sev, &timerid) == -1) {
        perror("Failed to create timer:");
        exit(1);
    }

    printf("INFO: timerid is %#jx\n", (uintmax_t)timerid);

    struct itimerspec its = {
        .it_value = {
            .tv_sec = TIMER_EXPIRE_TIME_US / 1000000000,
            .tv_nsec = TIMER_EXPIRE_TIME_US % 1000000000,
        },
        .it_interval = {
            .tv_sec = TIMER_EXPIRE_TIME_US / 1000000000,
            .tv_nsec = TIMER_EXPIRE_TIME_US % 1000000000,
        },
    };

    printf("INFO: sleep 2s ...\n");
    sleep(2);

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIG);

    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1) { // sigwaitinfo must block that SIG_BLOCK
        perror("Failed to block SIGRTMIN signal:");
        exit(1);
    }
    if (timer_settime(timerid, 0, &its, NULL) == -1) {
        perror("Failed to set time to timer:");
        exit(1);
    }

    siginfo_t si;
    int count = 0;
    printf("start running...\n");
    for(;;) {
        // usleep(1000);
        int sig = sigwaitinfo(&mask, &si);
        if (sig != SIG) continue;
        count ++;
        timer_t *tinfo = si.si_value.sival_ptr;
        int or = timer_getoverrun(*tinfo);
        if (or != 0 || count == 1000) {
            count = 0;
            printf("pthread caught signal %d, overrun: %d\n", sig, or);
        }
    }

    return NULL;
}

int main() {
    main_tid = pthread_self();
    printf("process id: %d\n", getpid());
    printf("thread_id %x\n", main_tid);

    // struct sched_param param = {};
    // param.sched_priority = sched_get_priority_max(SCHED_FIFO);

    // if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
    //     perror("Failed to set scheduler:");
    //     exit(1);
    // }
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIG);
    if (sigprocmask(SIG_SETMASK, &mask, NULL) == -1) {
        perror("Failed to block SIGRTMIN signal:");
        exit(1);
    }

    pthread_t tid;
    if (pthread_create(&tid, NULL, thread_handler, NULL) != 0) {
        perror("Failed to create thread:");
        exit(1);
    }

    for (;;) sleep(1);

    return 0;
}
