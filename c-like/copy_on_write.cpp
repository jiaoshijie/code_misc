#include <cstdio>
#include <string>

using namespace std;

int main(void)
{
  string str1 = "hello world";
  string str2 = str1;

  printf("Sharing the memory:\n");
  printf("str1 address: %p\n", str1.c_str());
  printf("str2 address: %p\n", str2.c_str());

  printf("After Copy-On-Write:\n");
  str1[1] = 'q';
  str2[1] = 'w';
  printf("str1: %s\n", str1.c_str());
  printf("str2: %s\n", str2.c_str());
  printf("str1 address: %p\n", str1.c_str());
  printf("str2 address: %p\n", str2.c_str());

  return 0;
}
