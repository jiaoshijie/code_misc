#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>

void *malloc(size_t size) {
    char buf[32];
    sprintf(buf, "Called malloc with the size %ld\n", size);

    // NOTE: Why I can't use puts(printf) function?
    // will get a segment fault error if using it.
    // https://stackoverflow.com/questions/48569950/malloc-with-ld-preload
    // NOTE: Because `puts` and `printf` function call `malloc` internally.
    // This will cause a recursive calling, then casue Segment Falut.
    // Using `LD_DEBUG=all` can view the ld-linux log.
    puts(buf);
    printf("%s", buf);
    // write(2, buf, strlen(buf));

    static void *(*real_malloc)(size_t) = NULL;

    real_malloc = dlsym(RTLD_NEXT, "malloc");
    if (real_malloc) {
        return real_malloc(size);
    }

    return NULL;
}
