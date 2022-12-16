#include "chead.h"

// char str[][5] = {
//   "jiao",
//   "_shi",
//   "_jie",
// };

int main(void)
{
  name_print("doublearray");
  stack_print();
  heap_print();

  // NOTICE: 二维数组 str[1] == *(str + 1)
  char str[][5] = {
    "jiao",
    "_shi",
    "_jie",
  };

  // NOTICE: print addr
  printf("\n");
  printf("* ---------------------------------------- *\n");
  printf("* -------------print address-------------- *\n");
  printf("* ---------------------------------------- *\n");
  printf("str addr: %p\n\n", &str);
  for (int i = 0; i < 3; i++)
  {
    printf("str[%d] addr: %p\t", i, &str[i]);
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
  // printf("\n\n");

  // NOTICE: print content
  printf("* ---------------------------------------- *\n");
  printf("* ------------print content--------------- *\n");
  printf("* ---------------------------------------- *\n");
  printf("str content: %p\n", str);
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
