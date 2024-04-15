#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>

size_t my_malloc_count = 0;

void *malloc(size_t size) {
    static void *(*real_malloc)(size_t) = NULL;

    if (real_malloc == NULL) {
        real_malloc = dlsym(RTLD_NEXT, "malloc");
    }
    my_malloc_count++;
    fprintf(stderr, "malloc count: %ld\n", my_malloc_count);
    return real_malloc(size);
}

