#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
  int file_pipe[2];
  int file_pipe2[2];
  pid_t pid;
  char buf[] = "wenjianguanli";
  char buf2[1024] = "";

  // file_pipe[0] is read, file_pipe[1] is write
  if(pipe(file_pipe) < 0)
  {
    perror("pipe()");
    exit(1);
  }

  if(pipe(file_pipe2) < 0)
  {
    perror("pipe()");
    exit(1);
  }

  if((pid = fork()) < 0)
  {
    perror("fork()");
    exit(1);
  }

  if(pid == 0)
  {
    /*close(file_pipe[0]);*/
    /*close(file_pipe2[1]);*/
    dup2(file_pipe[0], 0);
    dup2(file_pipe2[1], 1);
    /*write(file_pipe2[1], buf, strlen(buf));*/
    read(file_pipe[0], buf2, sizeof(buf2));
    printf("I am child process, and buf2 is %s\n", buf2);
  }
  else
  {
    /*read(file_pipe2[0], buf2, sizeof(buf2));*/
    write(file_pipe[1], buf, strlen(buf));
    /*printf("I am parent process, and buf2 = %s\n", buf2);*/
    printf("I am parent process\n");
  }

  return 0;
}
