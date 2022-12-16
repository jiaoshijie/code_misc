#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

// 查看文件是否有执行权限
void func1(char* path);

int main(void)
{
  printf("%ld\n", sizeof(unsigned short));
  return 0;
}

void func1(char* path)
{
struct stat st;
  if(stat(path, &st) == -1)
  {
    printf("stat error!\n");
    exit(1);
  }
  if(st.st_mode & S_IXUSR)
    printf("文件有可执行权限\n");
  else
    printf("文件无可执行权限\n");
}
