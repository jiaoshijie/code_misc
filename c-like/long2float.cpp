#include <iostream>

int main(void) {
  // long long v = 9'223'372'036'854'775'806ll;
  long long v = 33'554'431ll;  // 25 bits 1
  float f = static_cast<float>(v);  // 1 8 23(can represent 24)
  long long v1 = 18'014'398'509'481'983ll;  // 54 bits 1
  double b = static_cast<double>(v1);  // 1 11 52(can represent 53)
  int i = 0;
  printf("%lld\n%f\n", v, f);
  printf("----------------------\n");
  printf("%lld\n%lf\n", v1, b);
  return 0;
}
