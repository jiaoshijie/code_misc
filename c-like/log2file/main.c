#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#include "cJSON.h"

// thread related
static bool volatile g_running = true;
static bool g_has_content = false;
static pthread_cond_t g_cond;
static pthread_mutex_t g_mutex;

static uint64_t cycle_us = 1000;

#define ONE_KILOBYTE 1024

typedef struct {
    int32_t id;
    struct timespec t;
    double pos;
    double vel;
    double pos_cmd;
    double vel_cmd;
    uint32_t cpos;
}row_t;

#define ROWS_SIZE 8192

static uint8_t *g_rows[2];
static int g_rows_using_index = 0;
static uint8_t *g_row_offset;
static long long int g_row_real_len = 0;

void *write2file_thread(void *arg) {
    int fd = *(int *)arg;

    off_t offset = lseek(fd, 0, SEEK_CUR);
    if (offset >= ONE_KILOBYTE) {
        fprintf(stderr, "ERROR: File header size is %ld bytes, which should less than 1 KB.\n", offset);
        exit(1);
    }

    offset = lseek(fd, ONE_KILOBYTE, SEEK_SET);
    if (offset == (off_t)-1) {
        fprintf(stderr, "ERROR: lseek file cursor to 1 KB failed: %s\n", strerror(errno));
        exit(1);
    }

    uint8_t *one_rows = (uint8_t *)malloc(sizeof(uint8_t) * g_row_real_len * ROWS_SIZE);
    // error check

    while (g_running) {
        pthread_mutex_lock(&g_mutex);
        pthread_cond_wait(&g_cond, &g_mutex);
        int local_row_index = g_rows_using_index ^ 1;
        bool local_has_content = g_has_content;
        g_has_content = false;
        memcpy(one_rows, g_rows[local_row_index], g_row_real_len * ROWS_SIZE);
        pthread_mutex_unlock(&g_mutex);

        if (local_has_content) {
            printf("INFO: Sub thread: writing %d\n", local_row_index);
            if (write(fd, one_rows, g_row_real_len * ROWS_SIZE) == -1) {
                fprintf(stderr, "ERROR: Write to file failed: %s\n", strerror(errno));
                exit(1);
            }
            printf("INFO: Sub thread: writing %d finished\n", local_row_index);
        }
    }

    close(fd);
    printf("End of Sub Thread\n");
    return NULL;
}

row_t gen_a_row() {
    static int32_t i = 999;
    row_t ret;

    ret.id = i++;
    ret.pos = (double)i++;
    ret.vel = (double)i++;
    ret.pos_cmd = (double)i++;
    ret.vel_cmd = (double)i++;
    ret.cpos = (uint32_t)i++;

    clock_gettime(CLOCK_MONOTONIC, &ret.t);

    return ret;
}

void signal_handler(int sig) {
    (void)sig;
    printf("signal received\n");
    g_running = false;
}

int main() {
    if (signal(SIGTERM, signal_handler) == SIG_ERR) {
        fprintf(stderr, "ERROR: register signal for SIGTERM failed: %s\n", strerror(errno));
        exit(1);
    }
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        fprintf(stderr, "ERROR: register signal for SIGINT failed: %s\n", strerror(errno));
        exit(1);
    }

    int fd = open("./log.file", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        fprintf(stderr, "ERROR: Open file failed: %s\n", strerror(errno));
        exit(1);
    }

    cJSON *json = cJSON_CreateObject();  // error check
    cJSON_AddNumberToObject(json, "id", sizeof(int32_t));
    cJSON_AddNumberToObject(json, "t", sizeof(struct timespec));
    cJSON_AddNumberToObject(json, "pos", sizeof(double));
    cJSON_AddNumberToObject(json, "vel", sizeof(double));
    cJSON_AddNumberToObject(json, "pos_cmd", sizeof(double));
    cJSON_AddNumberToObject(json, "vel_cmd", sizeof(double));
    cJSON_AddNumberToObject(json, "cpos", sizeof(uint32_t));

    g_row_real_len = 2 * sizeof(int32_t) + sizeof(struct timespec) + 4 * sizeof(double);
    for (int i = 0; i < 2; i++) {
        g_rows[i] = (uint8_t *)malloc(sizeof(uint8_t) * g_row_real_len * ROWS_SIZE);
        // error check
    }

    g_row_offset = g_rows[g_rows_using_index];


    char *json_str = cJSON_PrintUnformatted(json);  // error check

    ssize_t len = write(fd, json_str, strlen(json_str));

    if (len == -1) {
        close(fd);
        fprintf(stderr, "ERROR: Write to file failed: %s\n", strerror(errno));
        exit(1);
    }

    cJSON_free(json_str);
    cJSON_Delete(json);

    pthread_t thread;
    int *p_fd = (int *)malloc(sizeof(int));
    if (!p_fd) {
        close(fd);
        fprintf(stderr, "ERROR: malloc failed for p_fd: %s\n", strerror(errno));
        exit(1);
    }
    *p_fd = fd;

    int local_row_index = g_rows_using_index;
    pthread_mutex_init(&g_mutex, NULL);
    pthread_cond_init(&g_cond, NULL); // error check

    pthread_create(&thread, NULL, write2file_thread, (void *)p_fd);
    struct timespec next_period;
    clock_gettime(CLOCK_MONOTONIC, &next_period);

    while (g_running) {
       next_period.tv_nsec += cycle_us * 1000;
       while (next_period.tv_nsec >= 10000000000ll) {
           next_period.tv_nsec -= 10000000000ll;
           next_period.tv_sec++;
       }

       clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &next_period, NULL);  // error check

       row_t row = gen_a_row();

       int32_t *pi32 = (int32_t *)g_row_offset;
       *pi32 = row.id;
       g_row_offset += sizeof(int32_t);

       struct timespec *ptime = (struct timespec *)g_row_offset;
       *ptime = row.t;
       g_row_offset += sizeof(struct timespec);

       double *pf64 = (double *)g_row_offset;
       *pf64 = row.pos;
       g_row_offset += sizeof(double);

       pf64 = (double *)g_row_offset;
       *pf64 = row.vel;
       g_row_offset += sizeof(double);

       pf64 = (double *)g_row_offset;
       *pf64 = row.pos_cmd;
       g_row_offset += sizeof(double);

       pf64 = (double *)g_row_offset;
       *pf64 = row.vel_cmd;
       g_row_offset += sizeof(double);

       uint32_t *pu32 = (uint32_t *)g_row_offset;
       *pu32 = row.cpos;
       g_row_offset += sizeof(uint32_t);

       if ((g_row_offset - g_rows[local_row_index]) >= (g_row_real_len * ROWS_SIZE)) {
           pthread_mutex_lock(&g_mutex);
           g_rows_using_index ^= 1;
           local_row_index = g_rows_using_index;
           g_has_content = true;
           pthread_mutex_unlock(&g_mutex);
           g_row_offset = g_rows[local_row_index];
           printf("INFO: Main thread: g_rows_using_index = %d\n", g_rows_using_index);
           // NOTE: singal write2file_thread
           pthread_cond_signal(&g_cond);
       }
    }

    pthread_mutex_unlock(&g_mutex);
    pthread_cond_signal(&g_cond);
    pthread_join(thread, NULL);
    pthread_cond_destroy(&g_cond);
    pthread_mutex_destroy(&g_mutex);
    printf("End of Main Thread\n");
    // close(fd);  // write2file_thread will close this file
    return 0;
}
