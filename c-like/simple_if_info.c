#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <linux/if_arp.h>
#include <arpa/inet.h>

// void get_if_list() {
//     struct if_nameindex *if_list, *iter;
//
//     if_list = if_nameindex();
//     if (if_list) {
//         for (iter = if_list; iter->if_index != 0 || iter->if_name != NULL; iter++) {
//             printf("%d:%s\n", iter->if_index, iter->if_name);
//         }
//     }
//
//     if_freenameindex(if_list);
// }

struct sif_info {
    char *name;
    int hw_family;
    unsigned char mac[6];
    int s_family;
    char *host;
    struct sif_info *next;
};

void insert_sif_info(struct sif_info **head, struct sif_info *node) {
    node->next = *head;
    *head = node;
}

void free_sif_info_node(struct sif_info *node) {
    if (node) {
        free(node->name);
        free(node->host);
        free(node);
    }
}

void free_sif_info(struct sif_info *head) {
    struct sif_info *node = head;
    while (node) {
        struct sif_info *tmp = node->next;
        free_sif_info_node(node);
        node = tmp;
    }
}

void print_sif_info(struct sif_info *head) {
    struct sif_info *node = head;
    while (node) {
        printf("%s: Type: %d", node->name, node->hw_family);
        if (node->hw_family == ARPHRD_ETHER) {
            printf(", Mac: ");
            for (int i = 0; i < 6; i++) {
                if (i != 5)
                    printf("%02X:", node->mac[i]);
                else
                    printf("%02X", node->mac[i]);
            }
        }
        if (node->s_family == AF_INET)
            printf(", IP Addr: %s", node->host);
        printf("\n");
        node = node->next;
    }
}

// ARPHRD_ETHER       ethernet interface type
// ARPHRD_CAN         can bus interface type
// ARPHRD_LOOPBACK    lo interface type
bool get_if_type(struct sif_info *node) {
    struct ifreq ifr;

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1) {
        return false;
    }

    strncpy(ifr.ifr_name, node->name, IFNAMSIZ - 1);

    if (ioctl(fd, SIOCGIFHWADDR, &ifr) != 0) {
        close(fd);
        return false;
    }

    node->hw_family = ifr.ifr_hwaddr.sa_family;

    if (ifr.ifr_hwaddr.sa_family == ARPHRD_ETHER) {
        memcpy(node->mac, ifr.ifr_addr.sa_data, 6);
    }

    close(fd);
    return true;
}

bool get_if_addr_list(struct sif_info **head) {
    struct ifaddrs *ifaddr_list = NULL, *iter;
    char host[NI_MAXHOST] = { 0 };
    struct sif_info *node = NULL;
    int ret = false;

    if (getifaddrs(&ifaddr_list) != 0) {
        return false;
    }

    for (iter = ifaddr_list; iter != NULL; iter = iter->ifa_next) {
        if (iter->ifa_addr) {
            if (iter->ifa_addr->sa_family == AF_INET) {
                node = (struct sif_info *)calloc(1, sizeof(struct sif_info));
                if (!node) goto failed;

                node->name = strdup(iter->ifa_name);
                if (!node->name) goto failed;

                if (!get_if_type(node)) goto failed;

                if (getnameinfo(iter->ifa_addr, sizeof(struct sockaddr_in),
                            host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST) != 0) {
                    goto failed;
                }

                node->s_family = iter->ifa_addr->sa_family;
                node->host = strdup(host);
                if (!node->host) goto failed;
            }
        } else {
            node = (struct sif_info *)calloc(1, sizeof(struct sif_info));
            if (!node) goto failed;

            node->name = strdup(iter->ifa_name);
            if (!node->name) goto failed;

            if (!get_if_type(node)) goto failed;
        }

        if (node)
            insert_sif_info(head, node);

        node = NULL;
    }

    ret = true;
failed:
    free_sif_info_node(node);
    freeifaddrs(ifaddr_list);
    return ret;
}

int main (void)
{
    struct sif_info *head = NULL;

    if (!get_if_addr_list(&head)) {
        printf("Got simple interface list failed\n");
        return -1;
    }
    print_sif_info(head);

    free_sif_info(head);
    return 0;
}
