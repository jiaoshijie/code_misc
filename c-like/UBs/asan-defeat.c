#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char a[128];
char b[128];

int main(int argc, char *argv[]) {
    strcpy(a + atoi(argv[1]), "owned.");
    printf("%s\n", b);
    return 0;
}
