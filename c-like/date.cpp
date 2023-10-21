#include <iostream>

bool is_runnain(int year) {
  return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int main(void) {
  int year_days = 365;
  int month_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int week[7] = {3, 4, 5, 6, 7, 1, 2};
  int year = 1999;
  int month = 12;
  int day = 24;
  size_t all_day = 0;
  for (int i = 1970; i < year; ++i) {
    all_day += year_days + (is_runnain(i) ? 1 : 0);
  }
  for (int i = 0; i < month - 1; ++i) {
    all_day += month_days[i];
  }
  all_day += month > 2 && is_runnain(year) ? 1 : 0;
  all_day += day;

  std::cout << week[all_day % 7] << std::endl;

  return 0;
}
