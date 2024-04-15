#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>

void *malloc(size_t size) {
    char buf[32];
    static void *(*real_malloc)(size_t) = NULL;
    if (real_malloc == NULL) {
        real_malloc = dlsym(RTLD_NEXT, "malloc");
    }
    sprintf(buf, "malloc called, size = %zu\n", size);
    write(2, buf, strlen(buf));
    return real_malloc(size);
}
