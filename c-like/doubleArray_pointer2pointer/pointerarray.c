#include "chead.h"

int main(void)
{
  name_print("pointerarray");
  stack_print();
  heap_print();
  // NOTICE: 指针数组
  char *str[] = {
    "jiao",
    "_shi",
    "_jie",
  };

  // printf("str size: %ld\n", sizeof(str));
  // printf("%s, %s, %s\n", str[0], str[1], str[2]);

  // NOTICE: print addr
  printf("\n");
  printf("* ---------------------------------------- *\n");
  printf("* -------------print address-------------- *\n");
  printf("* ---------------------------------------- *\n");
  printf("str addr: %p\n\n", &str);
  for (int i = 0; i < 3; i++)
  {
    printf("str[%d] addr: %p\n", i, &str[i]);
  }
  printf("\n\n");
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      printf("str[%d][%d] addr: %p\n", i, j, &str[i][j]);
    }
    printf("\n");
  }

  // NOTICE: print content
  printf("* ---------------------------------------- *\n");
  printf("* ------------print content--------------- *\n");
  printf("* ---------------------------------------- *\n");
  printf("str content: %p\n\n", str);
  for (int i = 0; i < 3; i++)
  {
    printf("str[%d] content: %p\n", i, str[i]);
  }
  printf("\n\n");
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      printf("str[%d][%d] content: %p\n", i, j, str[i][j]);
    }
    printf("\n");
  }

  return 0;
}
