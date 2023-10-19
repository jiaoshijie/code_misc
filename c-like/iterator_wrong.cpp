#include <iostream>
#include <cstring>
#include <stdexcept>
#include <cstdlib>

// TODO: std::initializer_list
struct A {
  char *ch;
  A() {
    ch = new char;
    *ch = 'A';
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

template<typename T>
class MyVector {
private:
  T *_inter;
  size_t _size;
  size_t _cap;
  void _realloc() {
    if (_size < _cap) return;
    if (_cap == 0) _cap = 1;
    else _cap *= 2;
    _inter = (T*)realloc(_inter, sizeof(T) * _cap);
  }
  void _realloc(size_t min_space) {
    if (_size < _cap) return;
    if (_cap == 0) _cap = 1;
    while (min_space > _cap) _cap * 2;
    _inter = (T*)realloc(_inter, sizeof(T) * _cap);
  }
public:
  MyVector() : _inter(nullptr), _size(0), _cap(0) {}
  MyVector(size_t _size) : _size(_size), _cap(_size) {  // with default value
    // https://stackoverflow.com/questions/3575458/does-new-call-default-constructor-in-c
    // _inter = new T[_size]{};
    _inter = (T*)malloc(sizeof(T) * _size);
    for (size_t i = 0; i < _size; i++) {
      _inter[i] = T{};
    }
  }
  MyVector(size_t _size, const T& _default_value) : _size(_size), _cap(_size) {
    _inter = (T*)malloc(sizeof(T) * _size);
    for (size_t i = 0; i < _size; i++) {
      _inter[i] = _default_value;
    }
  }
  // copy constructor
  MyVector(const MyVector& _other) {
    _size = _other._size;
    _cap = _other._cap;
    // FIXME: has bug, not call copy assignment or copy constructor for `T`;
    _inter = (T*)malloc(sizeof(T) * _size);
    memcpy(_inter, _other._inter, _size * sizeof(T));
  }
  // move constructor
  MyVector(MyVector&& _other) {
    _size = _other._size;
    _cap = _other._cap;
    _inter = _other._inter;
    _other._size = 0;
    _other._cap = 0;
    _other._inter = nullptr;
  }
  ~MyVector() {
    for (size_t i = 0; i < _size; i++) {
      _inter[i].~T();
    }
    _size = 0;
    _cap = 0;
    free(_inter);
    // delete[] _inter;
  }

  // copy assignment
  MyVector& operator=(const MyVector& _other) {
    _size = _other._size;
    _cap = _other._cap;
    _inter = (T*)malloc(sizeof(T) * _size);
    memcpy(_inter, _other._inter, _size * sizeof(T));
    return *this;
  }
  // move assignment
  MyVector& operator=(MyVector&& _other) {
    _size = _other._size;
    _cap = _other._cap;
    _inter = _other._inter;
    _other._size = 0;
    _other._cap = 0;
    _other._inter = nullptr;
    return *this;
  }

  T& at(size_t _pos) {
    if (_pos > _size) {
      std::out_of_range("Out of range!!!");
    }
    return _inter[_pos];
  }

  const T& at(size_t _pos) const {
    if (_pos > _size) {
      throw std::out_of_range("Out of range!!!");
    }
    return _inter[_pos];
  }

  T& operator[](size_t _pos) {
    return at(_pos);
  }
  const T& operator[](size_t _pos) const {
    return at(_pos);
  }

  T& front() {
    // NOTE: if _inter is empty, causes undefined behavior.
    return _inter[0];
  }

  T& back() {
    // NOTE: if _inter is empty, causes undefined behavior.
    return _inter[_size - 1];
  }

  T* data() {
    return _inter;
  }

  bool empty() {
    return 0 == _size;
  }

  size_t size() {
    return _size;
  }

  size_t capacity() {
    return _cap;
  }

  void reserve(size_t new_cap) {
    if (new_cap <= _cap) return;  // do nothing
    _cap = new_cap;
    // memory leak
    _inter = (T*)realloc(_inter, sizeof(T) * _cap);
  }

  // NOTE: need be more careful, when using it.
  // void shrink_to_fit() {}
  void clear() noexcept {
    _size = 0;
    // TODO: need to invalidate any references, pinters, or iterators referring to caontained elements.
  }

  // TODO
  // iterator insert() {}
  // TODO
  // iterator erase() {}

  void swap(MyVector& other) noexcept {
    MyVector temp = std::move(other);
    other = std::move(*this);
    (*this) = std::move(temp);
  }

  void resize(size_t count) {
    if (_size >= count) {
      _size = count;
    } else {
      if (count > _cap) {
        _realloc(count);
      }
      for (size_t i = _size; i < count; i++) {
        _inter[i] = T();
      }
      _size = count;
    }
  }
  void resize(size_t count, const T& value) {
    if (_size >= count) {
      // memory leak
      _size = count;
    } else {
      if (count > _cap) {
        _realloc(count);
      }
      for (size_t i = _size; i < count; i++) {
        _inter[i] = value;
      }
      _size = count;
    }
  }

  void pop_back() {
    if (_size == 0) return;
    _size -= 1;
    // TODO: invalidates end() iterator
  }

  void push_back(const T& value) {
    if (_size >= _cap) {
      _realloc();
    }
    _inter[_size++] = value;
  }
  void push_back(T&& value) {
    if (_size >= _cap) {
      _realloc();
    }
    _inter[_size++] = std::move(value);
  }
};

int main(void) {
  MyVector<A> v;
  v.push_back(A());
  // v.push_back(A());
  // v.push_back(12);
  // v.push_back(13);
  // v.push_back(14);
  // v.pop_back();
  // for (size_t i = 0; i < v.size(); i++) {
  //   std::cout << v.at(i) << std::endl;
  // }
  // A a;
  // std::cout << *(v[0].ch) << std::endl;
  // std::cout << *(a.ch) << std::endl;
  return 0;
}
