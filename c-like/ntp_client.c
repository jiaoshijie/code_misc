/*
 * (C) 2025 jiaoshijie.
 *
 * Compile: gcc ntp_client.c -o ntp_client -lm
 *
 * Usage: ./ntp_client 192.168.0.1
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

// https://labs.apnic.net/index.php/2014/03/10/protocol-basics-the-network-time-protocol/
// https://github.com/lettier/ntpclient/blob/master/source/c/main.c
// https://github.com/troglobit/sntpd

// #define NTP_DUMP_PACKET_INFO
#define NTP_PORT 123
#define NTP_TS_DELTA 2208988800ull  // For converting ntp time epoch to unix time epoch
#define TIMESPEC2US(ts) ((uint64_t)ts.tv_sec * 1000000 + (uint64_t)ts.tv_nsec / 1000)
#define NTP_SAMPLES_NUM 8
#define NTP_REQUEST_INTERVAL_S 2

/*
 * in the request package  (client -> server)
 * The client should fill out the `transmit timestamp` field.
 * In response the server will copy the transmit timestamp from the request
 * package into the originator timestamp field of response package.
 *
 * in the response package  (server -> client)
 *
 * ntp client                ntp server
 *     T1---------------------->
 *                              T2
 *        <---------------------T3
 *     T4
 * */

struct ntp_packet {
    uint8_t mode: 3;            // 0: reserved, 1: symmetric active, 2: symmetric passive, 3: client, 4: server, 5: broadcast, 6: reserved NTP control, 7: reserved private use
    uint8_t version_number: 3;  // 3 or 4, using 4
    uint8_t leap_indicator: 2;  // 0: no warning, 1: last minute has 61 seconds, 2: last minute has 59 seconds, 3: unsynchronized

    uint8_t stratum;
    int8_t poll;
    int8_t precision;

    // only useful in server msg
    uint16_t root_delay_s;
    uint16_t root_delay_f;
    uint16_t root_dispersion_s;
    uint16_t root_dispersion_f;

    uint32_t ref_id;
    uint32_t ref_ts_s;
    uint32_t ref_ts_f;

    // T1 in response
    uint32_t org_ts_s;
    uint32_t org_ts_f;
    // T2 in response
    uint32_t rx_ts_s;
    uint32_t rx_ts_f;
    // T3 in response
    uint32_t tx_ts_s;
    uint32_t tx_ts_f;
};
_Static_assert(sizeof(struct ntp_packet) == 48, "ntp packet size must be 48 bytes");

struct ntp_tuple {
    int64_t round_trip_delay_us;
    int64_t clock_offset_us;
};

static void report_error(const char *msg, bool quit) {
    perror(msg);
    if (quit) exit(1);
}

// year-month-day hour:minute:second.sub-second (UTC)
static void print_format_time(const char *desc, const struct tm *tm, const uint32_t frac) {
    assert(tm != NULL && desc != NULL);
    double sec = tm->tm_sec + (double)frac / (1ull << 32);
    printf("%s: %04d-%02d-%02d %02d:%02d:%09.6lf (UTC)\n", desc, tm->tm_year + 1900, tm->tm_mon + 1,
            tm->tm_mday, tm->tm_hour, tm->tm_min, sec);
}

static void pretty_print_ntp_packet(const struct ntp_packet *p) {
    assert(p != NULL);

    printf("LI: %u | VN: %u | MODE: %u\n", p->leap_indicator, p->version_number, p->mode);

    const char *stratum_str;
    if (p->stratum == 0)
        stratum_str = "Invalid ntp server";
    else if (p->stratum == 1)
        stratum_str = "Primary ntp server";
    else if (p->stratum == 16)
        stratum_str = "Unsynchronized";
    else
        stratum_str = "Secondary ntp server";
    assert(p->stratum <= 16);
    printf("stratum(The server hierarchy level): %u (%s)\n", p->stratum, stratum_str);
    if (p->stratum == 0) return;

    printf("poll(The suggested interval for the client to send sync msg): %d (%lfs)\n", p->poll, pow(2, p->poll));

    // TODO: make the time more readable
    // most OS precision is -20 ~ -24.
    printf("precision(The server's clock precision): %d (%lfs)\n", p->precision, pow(2, p->precision));


    //                round-trip delay
    //                  root delay
    // primary reference  <-->  ntp server  <-->  ntp client
    int16_t root_delay_s = ntohs(p->root_delay_s);
    uint16_t root_delay_f = ntohs(p->root_delay_f);
    float root_delay;
    if (root_delay_s < 0)
        root_delay = root_delay_s - (float)root_delay_f / (1u << 16);
    else // root_delay_s >= 0
        root_delay = root_delay_s + (float)root_delay_f / (1u << 16);
    printf("root delay: %fs\n", root_delay);

    int16_t root_dispersion_s = ntohs(p->root_dispersion_s);
    uint16_t root_dispersion_f = ntohs(p->root_dispersion_f);
    float root_dispersion;
    if (root_dispersion_s < 0)
        root_dispersion = root_dispersion_s - (float)root_dispersion_f / (1u << 16);
    else // root_dispersion_s >= 0
        root_dispersion = root_dispersion_s + (float)root_dispersion_f / (1u << 16);
    printf("root dispersion(max error due to clock frequency tolerance/accuracy): %fs\n", root_dispersion);

    // The ip is the server's sync source
    //      ref id                                me
    // higher level server  <-->  server  <-->  client
    printf("reference identifier: 0x%x\n", ntohl(p->ref_id));

    time_t sec;

    sec = ntohl(p->ref_ts_s) - NTP_TS_DELTA;
    print_format_time("reference timestamp  ", gmtime((const time_t *)&sec), ntohl(p->ref_ts_f));
    sec = ntohl(p->org_ts_s) - NTP_TS_DELTA;
    print_format_time("originator timestamp ", gmtime((const time_t *)&sec), ntohl(p->org_ts_f));
    sec = ntohl(p->rx_ts_s) - NTP_TS_DELTA;
    print_format_time("receive timestamp    ", gmtime((const time_t *)&sec), ntohl(p->rx_ts_f));
    sec = ntohl(p->tx_ts_s) - NTP_TS_DELTA;
    print_format_time("transmit timestamp   ", gmtime((const time_t *)&sec), ntohl(p->tx_ts_f));
}

// a - b
static int64_t ts_diff_us(struct timespec a, struct timespec b) {
    return TIMESPEC2US(a) - TIMESPEC2US(b);
}

static void dump_ntp_info(const struct ntp_packet *p, const struct timespec t1,
        const struct timespec t4) {
    printf("--------------------------------------------------------------\n");
    pretty_print_ntp_packet(p);
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

    // t1
    // t2 = t1 + t_d + t_o
    // t3 = t2 + t_p
    // t4 = t3 + t_d - t_o
    // t_p: system process time (not important)
    // t_d: one-way delay
    // t_o: clock offset (*)
    // t_2d: round-trip delay (*)

    // t_2d ≈ (t4 - t1) - (t3 - t2) = 2t_d
    // t_o ≈ ((t2 - t1) + (t3 - t4)) / 2

    struct timespec t2 = {
        .tv_sec = ntohl(p->rx_ts_s) - NTP_TS_DELTA,
        .tv_nsec = ((double)ntohl(p->rx_ts_f) / (1ull << 32)) * 1e9,
    };

    struct timespec t3 = {
        .tv_sec = ntohl(p->tx_ts_s) - NTP_TS_DELTA,
        .tv_nsec = ((double)ntohl(p->tx_ts_f) / (1ull << 32)) * 1e9,
    };

    int64_t t_2d = ts_diff_us(t4, t1) - ts_diff_us(t3, t2);
    int64_t t_o = (ts_diff_us(t2, t1) + ts_diff_us(t3, t4)) / 2;

    printf("round-trip delay: %ld us\n", t_2d);
    printf("clock offset: %ld us = %ld ms = %ld s\n", t_o, t_o / 1000, t_o / 1000000);
}

static void calculate_ntp_tuple(struct ntp_tuple *s, const struct ntp_packet *p,
        struct timespec t1, struct timespec t4) {
    struct timespec t2 = {
        .tv_sec = ntohl(p->rx_ts_s) - NTP_TS_DELTA,
        .tv_nsec = ((double)ntohl(p->rx_ts_f) / (1ull << 32)) * 1e9,
    };

    struct timespec t3 = {
        .tv_sec = ntohl(p->tx_ts_s) - NTP_TS_DELTA,
        .tv_nsec = ((double)ntohl(p->tx_ts_f) / (1ull << 32)) * 1e9,
    };

    s->round_trip_delay_us = ts_diff_us(t4, t1) - ts_diff_us(t3, t2);
    s->clock_offset_us = (ts_diff_us(t2, t1) + ts_diff_us(t3, t4)) / 2;
}

static struct ntp_tuple *ntp_client_process(const int sockfd,
        const struct sockaddr *addr, size_t *min_index) {
    static struct ntp_tuple samples[NTP_SAMPLES_NUM] = { 0 };
    if (min_index) *min_index = 0;

    for (int i = 0; i < NTP_SAMPLES_NUM; i++) {
#ifndef NTP_DUMP_PACKET_INFO
        printf("processing sample %d\n", i);
#endif
        struct timespec t1 = { 0 }, t4 = { 0 };
        struct ntp_packet p = {
            .version_number = 4,
            .mode = 3,
            .poll = log2(NTP_REQUEST_INTERVAL_S),
        };

        clock_gettime(CLOCK_REALTIME, &t1);
        p.tx_ts_s = htonl((uint32_t)(t1.tv_sec + NTP_TS_DELTA));
        p.tx_ts_f = htonl((uint32_t)((double)t1.tv_nsec / 1e9 * (1ull << 32)));
        ssize_t sent_len = sendto(sockfd, &p, sizeof(struct ntp_packet), 0,
                addr, sizeof(*addr));
        if (sent_len != sizeof(struct ntp_packet)) {
            return NULL;
        }

        ssize_t recv_len = recvfrom(sockfd, &p, sizeof(struct ntp_packet), 0, NULL, NULL);
        clock_gettime(CLOCK_REALTIME, &t4);
        if (recv_len != sizeof(struct ntp_packet)) {
            return NULL;
        }

#ifdef NTP_DUMP_PACKET_INFO
        dump_ntp_info(&p, t1, t4);
#endif
        calculate_ntp_tuple(&samples[i], &p, t1, t4);
        if (min_index && samples[i].round_trip_delay_us < samples[*min_index].round_trip_delay_us) {
            *min_index = i;
        }

        uint64_t interval = pow(2, p.poll);
        sleep(NTP_REQUEST_INTERVAL_S > interval ? interval : NTP_REQUEST_INTERVAL_S);
    }

    return samples;
}

static void timespec_add_us(struct timespec *ts, int64_t offset_us) {
    ts->tv_nsec += (offset_us % 1000000) * 1000;
    ts->tv_sec  += offset_us / 1000000;

    if (ts->tv_nsec >= 1000000000) {
        ts->tv_sec += ts->tv_nsec / 1000000000;
        ts->tv_nsec = ts->tv_nsec % 1000000000;
    } else if (ts->tv_nsec < 0) {
        ts->tv_sec -= (-ts->tv_nsec + 999999999) / 1000000000;
        ts->tv_nsec = (ts->tv_nsec % 1000000000 + 1000000000) % 1000000000;
    }
}

void ntp_client_apply_time(int64_t offset_us) {
    if (abs(offset_us) > 500 * 1000) {
        printf("Using clock_settime to update system time\n");
        struct timespec ts = { 0 };
        if (clock_gettime(CLOCK_REALTIME, &ts) != 0) {
            report_error("clock_gettime failed", false);
            return;
        }
        timespec_add_us(&ts, offset_us);
        if (clock_settime(CLOCK_REALTIME, &ts) != 0) {
            report_error("clock_settime failed", false);
            return;
        }
    } else {
        printf("Using adjtime to adjust sytem time\n");
        struct timeval delta = {
            .tv_usec = offset_us,
        };
        if (adjtime(&delta, NULL) != 0) {
            report_error("adjtime failed", false);
            return;
        }
    }

    printf("NTP client updated system time.\n");
}

int main(int argc, char *argv[]) {
    (void) argc;
    char *program_name = *argv++;
    if (*argv == NULL) {
        fprintf(stderr, "Usage: %s [ip address]\n", program_name);
        return 1;
    }

    const char *ip_addr = *argv++;

    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) {
        report_error("create UDP socket failed", true);
    }

    struct timeval timeout = {
        .tv_usec = 500 * 1000,  // 500ms
    };

    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        close(sockfd);
        report_error("setsockopt", true);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(NTP_PORT);
    if (inet_pton(AF_INET, ip_addr, &server_addr.sin_addr) <= 0) {
        close(sockfd);
        report_error("inet_pton failed", true);
    }

    size_t min_index = 0;
    struct ntp_tuple *samples = ntp_client_process(sockfd, (struct sockaddr *)&server_addr, &min_index);
    if (samples == NULL) {
        close(sockfd);
        report_error("ntp_client_process failed", true);
    }
#ifdef NTP_DUMP_PACKET_INFO
    printf("==============================================================\n");
    for (int i = 0; i < NTP_SAMPLES_NUM; i++) {
        printf("%d: round-trip delay: %ld us | clock offset: %ld us\n",
                i, samples[i].round_trip_delay_us, samples[i].clock_offset_us);
    }
    printf("the minimal round-trip time is %lu\n", min_index);
#else
    printf("round-trip delay: %ld us | clock offset: %ld us\n",
            samples[min_index].round_trip_delay_us, samples[min_index].clock_offset_us);
#endif
    ntp_client_apply_time(samples[min_index].clock_offset_us);

    close(sockfd);
    return 0;
}
