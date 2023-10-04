#include <iostream>
#include <cstring>
#include <string>
#include <vector>

// class && struct

// Big 3: class -> {constructor, destructor, copy constructor(copy assignment)}
// Rule 5: class -> {constructor, destructor, copy constructor(copy assignment), move constructor, move assignment}

class A {
  public:
    int *a;
    int len;
    std::string s;
    int b;
    int c;
    int d;
    A() {}
    A(int len, std::string s, int bb, int dd) : len(len), s(s), b(bb), d(dd), c(d) {
      std::cout << "constructor\n";
      this->a = new int[len];
      memset(this->a, 0, len * sizeof(int));
      a[0] = 10;
    }
    // copy constructor
    A(const A& a) {
      std::cout << "copy constructor\n";
      this->len = a.len;
      this->a = new int[len];
      this->s = a.s;
      memcpy(this->a, a.a, len * sizeof(int));
    }
    // move constructor
    A(A&& a) {
      std::cout << "move constructor\n";
      this->len = a.len;
      this->a = a.a;
      this->s = a.s;
      a.a = nullptr;
    }
    virtual ~A() {
      // std::cout << "destructor\n";
      delete[] this->a;
    }

    A& operator=(const A& a) {
      std::cout << "copy assignment\n";
      this->len = a.len;
      this->a = new int[len];
      memcpy(this->a, a.a, len * sizeof(int));
      this->s = a.s;
      return *this;
    }

    A& operator=(A&& a) {
      std::cout << "move assignment\n";
      this->len = a.len;
      this->a = a.a;
      this->s = std::move(a.s);
      a.a = nullptr;
      return *this;
    }

    void print() const {
      for (int i = 0; i < this->len; ++i) {
        std::cout << a[i] << std::endl;
      }
      std::cout << this->s << std::endl;
      std::cout << "b = " << this->b << std::endl;
      std::cout << "c = " << this->c << std::endl;
      std::cout << "d = " << this->d << std::endl;
    }

};

int main(void) {
  std::vector<A> v;
  v.reserve(10);
  for (int i = 1; i < 3; ++i) {
    A a(i, "jiao", 10, 10);
    // X: do something
    v.push_back(std::move(a));
    // v.push_back(A(i, "jiao", 10, 10));
    // v.emplace_back(i, "jiao", 1090, 2128982);
  }
  for (int i = 0; i < v.size(); ++i) {
    v[i].print();
  }
  return 0;
}
