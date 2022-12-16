#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
  // execl("../htdocs/color.py", "color.py", NULL);
  char *str = "wenjianguanli";

  printf("exit or runing! = %s", str);
  return 0;
}
