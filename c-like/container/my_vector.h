#ifndef __MY_VECTOR_H
#define __MY_VECTOR_H

#include <cstdlib>
#include <cstring>
#include <stdexcept>

namespace my_std {
  template<typename T>
    class Allocator {
      public:
        T* allocate(size_t _size) {
          return (T*)malloc(sizeof(T) * _size);
        }
        void deallocate(T* _ptr) {
          free(_ptr);
        }

        void construct(T* _ptr, const T& _value) {
          // new (placement-params) (type) initializer
          new (_ptr)T(_value);
        }
        void destroy(T* _ptr) {
          _ptr->~T();
        }
    };
  template<typename T, typename Alloc=Allocator<T>>
    class MyVector {
      private:
        Alloc *_alloc;
        T* _begin;
        T* _end;
        T* _now;
        void _realloc() {
          int cap = _end - _begin;
          int size = _now - _begin;
          T *t_begin = _begin;
          if (cap == 0) cap = 1;
          else cap *= 2;
          _begin = _alloc->allocate(cap);
          // TODO: maybe has problem
          memcpy(_begin, t_begin, sizeof(T) * size);
          _now = _begin + size;
          _end = _begin + cap;
          _alloc->deallocate(t_begin);
        }
        void _realloc(size_t count) {
          int cap = _end - _begin;
          int size = _now - _begin;
          T *t_begin = _begin;
          if (cap == 0) cap = 1;
          while (cap < count) cap *= 2;
          _begin = _alloc->allocate(cap);
          // TODO: maybe has problem
          memcpy(_begin, t_begin, sizeof(T) * size);
          _now = _begin + size;
          _end = _begin + cap;
          _alloc->deallocate(t_begin);
        }
      public:
        MyVector() : _alloc(new Allocator<T>), _begin(nullptr), _end(nullptr), _now(nullptr) {}
        MyVector(size_t _size) : _alloc(new Allocator<T>) {
          _begin = _alloc->allocate(_size);
          _end = _begin + _size;
          _now = _end;
          for (T* it = _begin; it != _end; ++it) {
            new (it)T{};  // default constuctor
          }
        }
        MyVector(size_t _size, const T& _value) : _alloc(new Allocator<T>) {
          _begin = _alloc->allocate(_size);
          _end = _begin + _size;
          _now = _end;
          for (T* it = _begin; it != _end; ++it) {
            _alloc->construct(it, _value);
          }
        }
        // copy constructor
        MyVector(const MyVector& _other) {
          size_t size = _other._now - _other._begin;
          _begin = _alloc->allocate(size);
          _end = _begin + size;
          _now = _end;
          T* it = _begin;
          T* o_it = _other._begin;
          for (; it != _end; ++it, ++o_it) {
            // _alloc->construct(it, *o_it);
            *it = *o_it;
          }
        }
        // move constructor
        MyVector(MyVector&& _other) {
          _begin = _other._begin;
          _end = _other._end;
          _now = _other._now;
          _other._begin = nullptr;
          _other._end = nullptr;
          _other._now = nullptr;
        }
        ~MyVector() {
          for (T* it = _begin; it != _now; it++) {
            _alloc->destroy(it);
          }
          _alloc->deallocate(_begin);
          _begin = nullptr;
          _end = nullptr;
          _now = nullptr;
          delete _alloc;
        }

        // copy assignment
        MyVector& operator=(const MyVector& _other) {
          size_t size = _other._now - _other._begin;
          _begin = _alloc->allocate(size);
          _end = _begin + size;
          _now = _end;
          T* it = _begin;
          T* o_it = _other._begin;
          for (; it != _end; ++it, ++o_it) {
            *it = *o_it;
          }
          return *this;
        }

        // move assignment
        MyVector& operator=(MyVector&& _other) {
          _begin = _other._begin;
          _end = _other._end;
          _now = _other._now;
          _other._begin = nullptr;
          _other._end = nullptr;
          _other._now = nullptr;
          return *this;
        }

        // const version
        T& at(size_t _pos) {
          if (_pos > _now - _begin) {
            std::out_of_range("out of range!!!");
          }
          return *(_begin + _pos);
        }

        // const version
        T& operator[](size_t _pos) {
          return at(_pos);
        }

        // const version
        T& front() {
          // NOTE: if _begin == _now; causes undefined behavior.
          return *_begin;
        }

        // const version
        T& back() {
          // NOTE: if _begin == _now; causes undefined behavior.
          return *(_now - 1);
        }

        // const version
        T* data() {
          return _begin;
        }

        bool empty() {
          return _begin == _now;
        }

        size_t size() {
          return _now - _begin;
        }

        size_t capacity() {
          return _end - _begin;
        }

        void reserve(size_t new_cap) {
          if (new_cap < _end - _begin) return;  // do nothing
          int size = _now - _begin;
          T *t_begin = _begin;
          _begin = _alloc->allocate(new_cap);
          _end = _begin + new_cap;
          _now = _begin + size;
          memcpy(_begin, t_begin, sizeof(T) * size);
          _alloc->deallocate(t_begin);
        }

        // NOTE: need be more careful, when using `shrink_to_fit()`.
        // void shrink_to_fit()

        void clear() noexcept {
          for (T* it = _begin; it != _now; ++it) {
            _alloc->destroy(it);
          }
          _now = _begin;
        }

        // TODO:
        // iterator insert() {}
        // TODO:
        // iterator erase() {}

        void swap(MyVector& _other) noexcept {
          MyVector temp = std::move(_other);
          _other = std::move(*this);
          *this = std::move(temp);
        }

        void resize(size_t count) {
          if (count == _now - _begin) return;
          if (count < _now - _begin) {
            for (T* it = _begin + count; it != _now; ++it) {
              _alloc->destroy(it);
            }
            _now = _begin + count;
          } else {  // count > _now - _begin
            if (count > _end - _begin) {
              _realloc(count);
            }
            for (T* it = _now; it != _begin + count; ++it) {
              *it = T();
            }
            _now = _begin + count;
          }
        }
        void resize(size_t count, const T& value) {
          if (count == _now - _begin) return;
          if (count < _now - _begin) {
            for (T* it = _begin + count; it != _now; ++it) {
              _alloc->destroy(it);
            }
            _now = _begin + count;
          } else {  // count > _now - _begin
            if (count > _end - _begin) {
              _realloc(count);
            }
            for (T* it = _now; it != _begin + count; ++it) {
              // _alloc->construct(it, value);
              *it = value;
            }
            _now = _begin + count;
          }
        }

        void pop_back() {
          // undefined behavior
          if (_now == _begin) return;
          _now--;
          _alloc->destroy(_now);
        }

        void push_back(const T& _value) {
          if (_now == _end) {
            _realloc();
          }
          *(_now++) = _value;
          // _alloc->construct(_now++, _value);
        }

        void push_back(T&& _value) {
          if (_now == _end) {
            _realloc();
          }
          *(_now++) = std::move(_value);
        }

        class iterator {
          private:
            // Properties of our pointer
            using Categary = std::forward_iterator_tag;
            using Distance = std::ptrdiff_t;
            // Shorthand
            using Pointer = T*;
            using Reference = T&;
            using Value = T;
            Pointer _ptr;
          public:
            iterator(Pointer _ptr) : _ptr(_ptr) {}
            Reference operator*() const {
              return *_ptr;
            }
            Pointer operator->() const {
              return _ptr;
            }

            bool operator==(const iterator& rhs) const {
              return _ptr == rhs.ptr;
            }
            bool operator!=(const iterator& rhs) const {
              return _ptr != rhs._ptr;
            }

            // suffix `++it`
            iterator& operator++() {
              _ptr++;
              return *this;
            }
            // postfix `it++`
            iterator operator++(T) {
              iterator old = *this;
              _ptr++;
              return old;
            }
        };

        iterator begin() {
          return iterator(_begin);
        }
        iterator end() {
          return iterator(_now);
        }
        // rbegin, rend, cbegin, cend, crbegin, crend
    };
};


#endif  // __MY_VECTOR_H
