#include "head/chead.h"

int main(int argc, char *argv[])
{

  stack_print();

#if 0
  // printf("%d, %s, %s, %s, %s, %c\n", argc, *argv, argv[0], argv[1], *(argv + 1), *(*(argv + 1) + 3));
  // printf("%p, %p, %p, %p, %p, %p, %p, %p, %p\n",
  //     &argc, &argv, argv, &argv[0], &argv[1], argv[0], argv[1], argv[2], argv[3]);
#endif

#if 0
  // NOTICE 在栈空间中
  char str[][5] = {
    "jiao",
    "_shi",
    "_jie",
  };
  // printf("str = %s, addr = %p\n", str, str);
  printf("str0 = %s, addr = %p, addr2 = %p\n", str[0], str[0], &str[0]);
  printf("str1 = %s, addr = %p, addr2 = %p\n", str[1], str[1], &str[1]);
  printf("str2 = %s, addr = %p, addr2 = %p\n", str[2], str[2], &str[2]);
  // printf("str00 = %c, addr = %p\n", str[0][0], &str[0][0]);
  // printf("str00 = %c\n", *(*(str) + 0));
  // printf("str1 = %c\n", *(*(str + 1) + 1));
#endif

#if 1
  // NOTICE 在堆空间中
  char **str = (char **)malloc(sizeof(char*) * 3);
  for (int i = 0; i < 3; i++)
   *(str + i) = (char *)malloc(sizeof(char) * 5);
  // char **str = (char **)malloc(sizeof(char) * 3 * 5);

  // memcpy(*(str + 0), "jiao", 5);
  // memcpy(*(str + 1), "_shi", 5);
  // memcpy(*(str + 2), "_jie", 5);
  // 赋值时给错了地址
  memcpy((str + 0), "jiao", 5);
  memcpy((str + 1), "_shi", 5);
  memcpy((str + 2), "_jie", 5);

  printf("straddr = %p\n", &str);
  // printf("str1 = %c\n", *(*(str + 1) + 1));

  printf("str0's addr = %p, str0 = %s, str0 = %p,%c\n", str + 0, str + 0, *(str + 0), *(str + 0));
  printf("str1's addr = %p, str1 = %s, str1 = %p,%c\n", str + 1, str + 1, *(str + 1), *(str + 1));
  printf("str2's addr = %p, str2 = %s, str2 = %p,%c\n", str + 2, str + 2, *(str + 2), *(str + 2));
  printf("str = %s\n", str);
  // printf("str = %s\n", *(str + 0));
  // free(str);
  // printf("%s\n", *(str + 0));

#endif

#if 0

  char **str = (char **)malloc(sizeof(char*) * 3);

  char *sch0 = "jiao";
  char *sch1 = "_shi";
  char *sch2 = "_jie";

  str[0] = sch0;
  str[1] = sch1;
  str[2] = sch2;

  printf("str addr is %p, and contents is %p, sch0's contents is %p\n", &str, str, sch0);
  printf("str[0] = %s, addr = %p\n", str[0], str[0]);
  printf("*(str + 0) = %s, addr = %p\n", *(str + 0), *(str + 0));
  printf("(str + 0) = %s, addr = %p\n", (str + 0), (str + 0));

#endif

#if 0
  char *str[] = {
    "jiao",
    "_shi",
    "_jie",
  };

  // printf("str_len = %ld\n", sizeof(str));
  // printf("str_len = %ld\n", sizeof(str[1]));

  // printf("str1 = %s, str2 = %s, str3 = %s\n", str[0], *(str + 1), str[2]);
  // printf("str1 = %c\n", *(*(str + 1) + 1));
  printf("str0 = %s, addr = %p, %p, addr2 = %p, %p\n", str[0], str[0], *(str + 0), &str[0], str + 0);
  printf("str1 = %s, addr = %p, %p, addr2 = %p, %p\n", str[1], str[1], *(str + 1), &str[1], str + 1);
  printf("str2 = %s, addr = %p, %p, addr2 = %p, %p\n", str[2], str[2], *(str + 2), &str[2], str + 2);

#endif
  return 0;
}
