#include <stdlib.h>

int main(void)
{
  // int array[] = { 0, 1, 2, 3, 4 };
  int **array = (int **)malloc(sizeof(int *) * 5);
  for (int i = 0; i < 5; i++)
    array[i] = (int *)malloc(sizeof(int));
  void *a1 = (void *)&array, *a2 = (void *)array;
  return 0;
}
