#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <math.h>

// https://labs.apnic.net/index.php/2014/03/10/protocol-basics-the-network-time-protocol/
// https://github.com/lettier/ntpclient/blob/master/source/c/main.c
// https://github.com/troglobit/sntpd

// #define NTP_IP "192.168.0.41"
#define NTP_IP "162.159.200.1"
#define NTP_PORT 123
#define NTP_TS_DELTA 2208988800ull  // For converting ntp time epoch to unix time epoch
#define NTP_TS_FRAC_MASK32 0x0000FFFFul
#define NTP_TS_FRAC_MASK16 0x00FFul

/*
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
    uint32_t root_delay;       // 16.16 FP
    uint32_t root_dispersion;  // 16.16 FP
    uint32_t ref_id;
    uint64_t ref_timestamp;    // 32.32 FP
    uint64_t orig_timestamp;   // 32.32 FP   T1
    uint64_t recv_timestamp;   // 32.32 FP   T2
    uint64_t trans_timestamp;  // 32.32 FP   T3
};
_Static_assert(sizeof(struct ntp_packet) == 48, "ntp packet size must be 48 bytes");

void pretty_print_ntp_packet(struct ntp_packet *p) {
    assert(p != NULL);

    printf("LI: %u | VN: %u | MODE: %u\n"
            "stratum: %u\n"
            "poll: %d\n"
            "precision: %d\n"
            "root delay: %x.%x\n"
            "root dispersion: %x.%x\n"
            "reference id: %u\n"
            "reference timestamp: %x.%x\n"
            "originate timestamp(T1): %x.%x\n"
            "receive timestamp(T2): %x.%x\n"
            "transmit timestamp(T3): %x.%x\n",
            p->leap_indicator, p->version_number, p->mode, p->stratum,
            p->poll, p->precision,
            p->root_delay >> 16, (uint16_t)(p->root_delay & NTP_TS_FRAC_MASK16),
            p->root_dispersion >> 16, (uint16_t)(p->root_dispersion & NTP_TS_FRAC_MASK16),
            p->ref_id,
            (uint32_t)(p->ref_timestamp >> 32),
            (uint32_t)(p->ref_timestamp & NTP_TS_FRAC_MASK32),
            (uint32_t)(p->orig_timestamp >> 32),
            (uint32_t)(p->orig_timestamp & NTP_TS_FRAC_MASK32),
            (uint32_t)(p->recv_timestamp >> 32),
            (uint32_t)(p->recv_timestamp & NTP_TS_FRAC_MASK32),
            (uint32_t)(p->trans_timestamp >> 32),
            (uint32_t)(p->trans_timestamp & NTP_TS_FRAC_MASK32));
}

int main() {
    struct ntp_packet p = {
        .version_number = 4,
        .mode = 3,
    };

    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) {
        perror("create UDP socket failed");
        exit(1);
    }

    struct timeval timeout = {
        .tv_usec = 500 * 1000,  // 500ms
    };

    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        perror("setsockopt");
        close(sockfd);
        exit(1);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(NTP_PORT);
    if (inet_pton(AF_INET, NTP_IP, &server_addr.sin_addr) <= 0) {
        perror("inet_pton failed");
        close(sockfd);
        exit(1);
    }

    ssize_t sent_len = sendto(sockfd, &p, sizeof(struct ntp_packet), 0,
            (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (sent_len != sizeof(struct ntp_packet)) {
        perror("sendto npt server failed");
        close(sockfd);
        exit(1);
    }
    printf("send ntp package\n");

    struct sockaddr_in recv_addr;
    socklen_t addr_len = sizeof(recv_addr);
    ssize_t recv_len = recvfrom(sockfd, &p, sizeof(struct ntp_packet), 0,
                                (struct sockaddr *)&recv_addr, &addr_len);
    if (recv_len != sizeof(struct ntp_packet)) {
        perror("recvfrom ntp server failed");
        close(sockfd);
        exit(1);
    }

    close(sockfd);
    pretty_print_ntp_packet(&p);
    return 0;
}
