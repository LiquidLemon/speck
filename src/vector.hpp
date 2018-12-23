#pragma once

template <size_t size, typename T>
class Vector {
  public:
    Vector() = default;
    Vector(std::initializer_list<T> values);
    ~Vector() = default;

    T& operator[](size_t index);

    T data[size];
};

template <size_t size, typename T>
Vector<size, T>::Vector(std::initializer_list<T> values) {
  static_assert(values.size() == size, "Incorrect number of values");
  std::copy(values.begin(), values.end(), data);
}

template <size_t size, typename T>
T& Vector<size, T>::operator[](size_t index) {
  return data[index];
}

template <typename T>
using Vector3 = Vector<3, T>;

using Vector3f = Vector3<float>;
