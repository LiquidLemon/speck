#pragma once
#include <cstdlib>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>

template <size_t size, typename T>
class Vector {
  public:
    Vector() = default;
    Vector(std::initializer_list<T> values);
    ~Vector() = default;
    Vector cross(Vector other);

    T& operator[](size_t index);

  protected:
    T data[size];
};

template <size_t size, typename T>
Vector<size, T>::Vector(std::initializer_list<T> values) {
  if (values.size() != size) {
    throw std::runtime_error("Incorrect number of values for Vector");
  }
  std::copy(values.begin(), values.end(), data);
}


template <size_t size, typename T>
T& Vector<size, T>::operator[](size_t index) {
  return data[index];
}


template <typename T>
using Vector3 = Vector<3, T>;

using Vector3f = Vector3<float>;

template <typename T>
using Vector2 = Vector<2, T>;

using Vector2i = Vector2<int>;

