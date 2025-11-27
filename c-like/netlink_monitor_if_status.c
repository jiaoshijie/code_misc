#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#include <time.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <linux/if.h>

static void parse_rtattr(struct rtattr *rta, int len) {
    char *eth_name = NULL;
    struct timespec t;

    while (RTA_OK(rta, len)) {
        switch (rta->rta_type) {
            case IFLA_IFNAME:
                eth_name = ((char *)RTA_DATA(rta));
                break;
            case IFLA_OPERSTATE:
                if (*(uint8_t *)RTA_DATA(rta) == IF_OPER_UP) {
                    clock_gettime(CLOCK_MONOTONIC, &t);
                    printf("if: %s, state: up, sec: %ld, nsec: %ld\n",
                            eth_name, t.tv_sec, t.tv_nsec);
                } else if (*(uint8_t *)RTA_DATA(rta) == IF_OPER_DOWN) {
                    clock_gettime(CLOCK_MONOTONIC, &t);
                    printf("if: %s, state: down, sec: %ld, nsec: %ld\n",
                            eth_name, t.tv_sec, t.tv_nsec);
                }
                break;
        }
        rta = RTA_NEXT(rta, len);
    }
}

static void io_handle_nl_link_msg(char *buf, size_t buf_len) {
    struct nlmsghdr *nlh;
    struct ifinfomsg *ifi;
    struct rtattr *rta;

    // 解析Netlink消息
    for (nlh = (struct nlmsghdr *)buf; NLMSG_OK(nlh, buf_len);
            nlh = NLMSG_NEXT(nlh, buf_len)) {
        if (nlh->nlmsg_type == NLMSG_DONE)
            break;

        if (nlh->nlmsg_type == RTM_NEWLINK) {  // 链路状态变化消息
            ifi = (struct ifinfomsg *)NLMSG_DATA(nlh);
            rta = (struct rtattr *)IFLA_RTA(ifi);
            int rta_len = IFLA_PAYLOAD(nlh);

            parse_rtattr(rta, rta_len);
        }
    }
}

static int create_netlink_socket() {
    int sockfd;
    struct sockaddr_nl addr;

    sockfd = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (sockfd < 0) {
        fprintf(stderr, "require netlink socket failed: %s\n", strerror(errno));
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.nl_family = AF_NETLINK;
    addr.nl_groups = RTMGRP_LINK;
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        fprintf(stderr, "bind netlink socket failed: %s\n", strerror(errno));
        close(sockfd);
        return -1;
    }

    return sockfd;
}

int main() {
    int sock = create_netlink_socket();
    assert(sock != -1 && "create netlink socket failed");
    char buffer[4096] = { 0 };
    int len = 0;

    while ((len = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
        io_handle_nl_link_msg(buffer, len);
    }

    if (len <= 0) {
        fprintf(stderr, "receive data from nl_socket failed: %s\n", strerror(errno));
    }
    return 0;
}
