#define _GNU_SOURCE
#include <sched.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv) {
    (void)argc;

    argv++;

    if (!*argv) {
        fprintf(stderr, "Error: Need input a pid number\n");
        exit(-1);
    }

    pid_t p = (pid_t)atoi(*argv);
    if (p == 0) {
        fprintf(stderr, "Error: Invalid pid number\n");
        exit(-1);
    }

    fprintf(stdout, "Process ID: %d\n", p);

    int cpu_core = 3;

    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(cpu_core, &cpuset);

    if (-1 == sched_setaffinity(p, sizeof(cpuset), &cpuset)) {
        fprintf(stderr, "Error: set process to cpu core %d failed, becasue of %s\n",
                cpu_core, strerror(errno));
        exit(-1);
    }

    fprintf(stdout, "Set Process to Cpu Core %d\n", cpu_core);

    struct sched_param param = {};
    param.sched_priority = sched_get_priority_max(SCHED_FIFO);

    if (-1 == sched_setscheduler(p, SCHED_FIFO, &param)) {
        fprintf(stderr, "Error: make process rt scheudled failed, becuase of %s\n",
                strerror(errno));
        exit(-1);
    }

    fprintf(stdout, "Make Process rt Scheudled\n");

    return 0;
}
