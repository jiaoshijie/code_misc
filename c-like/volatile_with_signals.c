#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>

volatile bool sig_arrived = false;

void handler(int sig) {
  if (sig == SIGINT) {
    sig_arrived = true;
  }
}

int main(void) {
  printf("Waiting for pressing Ctrl-C to move on.\n");
  signal(SIGINT, handler);
  while (!sig_arrived) {}
  printf("done\n");
  return 0;
}
