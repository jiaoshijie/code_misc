#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd = open("/dev/mydevice", O_RDWR);
    if (fd == -1) {
        printf("open failed\n");
        return -1;
    }

    printf("open was successful\n");
    close(fd);
    return 0;
}
