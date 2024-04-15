#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>

size_t my_free_count = 0;

void free(void *p) {
    static void (*real_free)(void *) = NULL;

    if (real_free == NULL) {
        real_free = dlsym(RTLD_NEXT, "free");
    }
    my_free_count++;
    fprintf(stderr, "free count: %ld\n", my_free_count);
    real_free(p);
}
