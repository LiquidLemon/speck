#pragma once
#include <cstdlib>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include <cmath>

template <size_t size, typename T>
class Vector {
  public:
    Vector() = default;
    Vector(std::initializer_list<T> values);
    ~Vector() = default;
    Vector cross(Vector other);
    Vector operator^(Vector other);
    T operator*(Vector other);
    Vector operator-(Vector other);
    Vector operator+(Vector other);

    float length();
    void normalize();

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

template <size_t size, typename T>
Vector<size, T> Vector<size, T>::operator^(Vector other) {
  return cross(other);
}

template <size_t size, typename T>
T Vector<size, T>::operator*(Vector other) {
  T product = T(0);
  for (size_t i = 0; i < size; i++) {
    product += data[i] * other[i];
  }
  return product;
}

template <size_t size, typename T>
Vector<size, T> Vector<size, T>::operator+(Vector other) {
  Vector<size, T> result;
  for (size_t i = 0; i < size; i++) {
    result[i] = data[i] + other[i];
  }
  return result;
}

template <size_t size, typename T>
Vector<size, T> Vector<size, T>::operator-(Vector other) {
  Vector<size, T> result;
  for (size_t i = 0; i < size; i++) {
    result[i] = data[i] - other[i];
  }
  return result;
}

template <size_t size, typename T>
float Vector<size, T>::length() {
  float sum = 0;
  for (size_t i = 0; i < size; i++) {
    sum += data[i] * data[i];
  }
  return sqrt(sum);
}

template <size_t size, typename T>
void Vector<size, T>::normalize() {
  auto length = this->length();
  for (size_t i = 0; i < size; i++) {
    data[i] = data[i] / length;
  }
}
