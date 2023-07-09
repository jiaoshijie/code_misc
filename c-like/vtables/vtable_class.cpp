//    A
//   / \
//  /   \
// B     C
// \    /
//  \  /
//   D

class A {
public:
  ~A() = default;
  virtual void a_foo() {}
};

class B : virtual public A {
public:
  virtual void b_foo() {}
};

class C : virtual public A {
public:
  virtual void c_foo() {}
};

class D : public B, public C {
public:
};

int main(void) {
  D *d = new D;
  int breakpoint = 0;
  return 0;
}
