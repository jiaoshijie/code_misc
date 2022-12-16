#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(void)
{
  pid_t fpid;
  int count = 0;
  fpid = fork();

  if(fpid < 0)
    printf("fork() error!\n");
  else if(fpid == 0)
  {
    printf("I am the child process, my process id is %d\n", 
        getpid());
    count++;
  }
  else
  {
    printf("I am the parent process, my process id is %d\n", 
        getpid());
    count++;
  }
  printf("count = %d\n", count);

  return 0;
}
