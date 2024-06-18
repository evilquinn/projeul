
#pragma once

#include <iostream>
#include <type_traits>

template <typename T>
class annotator : public T {
 public:
  template <typename... ArgTs>
  annotator(ArgTs&&... args) : T(std::forward<ArgTs>(args)...) {
    std::cout << "ctor:        " << (void*)this << std::endl;
  }
  ~annotator() { std::cout << "dtor:        " << (void*)this << std::endl; }
  // TODO type traits for each of the following special members to ensure T has them...
  annotator(const annotator& other) : T(other) {
    std::cout << "copy ctor:   " << (void*)this << std::endl;
  }
  annotator& operator=(const annotator& other) {
    T::operator=(other);
    std::cout << "copy assign: " << (void*)this << std::endl;
    return *this;
  }
  annotator(annotator&& other) : T(std::forward<T>(other)) {
    std::cout << "move ctor:   " << (void*)this << std::endl;
  }
  annotator& operator=(annotator&& other) {
    T::operator=(std::forward<T>(other));
    std::cout << "move assign: " << (void*)this << std::endl;
    return *this;
  }

 private:
  // implement way for caller to provide specific ostream later
};
