class A {
public:
  A() = default;
  ~A() = default;

  virtual void vfoo_1() {}
  virtual void vfoo_2() {}
};

int main(void) {
  A *a = new A;
  int breakpoint = 0;
  return 0;
}
