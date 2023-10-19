#include <iostream>

#include "./my_vector.h"

struct A {
  char *ch;
  A() {
    ch = new char;
    *ch = 'A';
  }
  A(const char c) {
    ch = new char;
    *ch = c;
  }
  ~A() {
    delete ch;
  }
  A(const A& a) {
    ch = new char;
    *ch = *a.ch;
  }
  A(A&& a) {
    ch = a.ch;
    a.ch = nullptr;
  }
  A& operator=(const A& a) {
    ch = new char;
    *ch = *a.ch;
    return *this;
  }
  A& operator=(A&& a) {
    ch = a.ch;
    a.ch = nullptr;
    return *this;
  }
};

int main(void) {
  my_std::MyVector<A> v;
  std::cout << v.size() << " " << v.capacity() << std::endl;
  v.push_back(A('b'));
  v.push_back(A('c'));
  v.push_back(A('d'));
  v.resize(5, 'a');
  // v.pop_back();
  // v.pop_back();
  std::cout << v.size() << " " << v.capacity() << std::endl;
  // auto it = v.begin();
  // std::cout << *(*it).ch << std::endl;
  for (auto it = v.begin(); it != v.end(); it++) {
    std::cout << *(it->ch) << std::endl;
  }
  return 0;
}
