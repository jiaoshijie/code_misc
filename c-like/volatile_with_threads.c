#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

volatile bool done = false;

void *th_func(void *) {
  sleep(1);
  done = true;
  return NULL;
}

int main(void) {
  pthread_t th;
  pthread_create(&th, NULL, th_func, NULL);
  printf("waiting...\n");
  while(!done) {}
  printf("done\n");
  pthread_join(th, NULL);
  return 0;
}
