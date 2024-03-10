#include "chead.h"

int main(void)
{
  name_print("doublepointer");
  stack_print();
  heap_print();

  char **d_ptr = (char **)malloc(sizeof(char *) * 3);
  for (int i = 0; i < 3; i++)
  {
    d_ptr[i] = (char *)malloc(sizeof(char) * 5);
  }

  memcpy(d_ptr[0], "jiao", 5);
  memcpy(d_ptr[1], "_shi", 5);
  memcpy(d_ptr[2], "_jie", 5);

  // printf("%s\n", d_ptr[0]);
  // printf("%s\n", d_ptr[1]);
  // printf("%s\n", d_ptr[2]);
  // NOTICE: print addr
  printf("\n");
  printf("* ---------------------------------------- *\n");
  printf("* -------------print address-------------- *\n");
  printf("* ---------------------------------------- *\n");
  printf("d_ptr addr: %p\n\n", &d_ptr);
  for (int i = 0; i < 3; i++)
  {
    printf("d_ptr[%d] addr: %p\n", i, &d_ptr[i]);
  }
  printf("\n\n");
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      printf("d_ptr[%d][%d] addr: %p\n", i, j, &d_ptr[i][j]);
    }
    printf("\n");
  }


  // NOTICE: print content
  printf("* ---------------------------------------- *\n");
  printf("* ------------print content--------------- *\n");
  printf("* ---------------------------------------- *\n");
  printf("d_ptr content: %p\n", d_ptr);
  for (int i = 0; i < 3; i++)
  {
    printf("d_ptr[%d] content: %p\n", i, d_ptr[i]);
  }
  printf("\n\n");
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      printf("d_ptr[%d][%d] content: %p\n", i, j, d_ptr[i][j]);
    }
    printf("\n");
  }

  return 0;
}
