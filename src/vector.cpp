#include "vector.hpp"

template <>
Vector3f Vector3f::cross(Vector3f other) {
  Vector3f product;
  return {
    data[1] * other[2] - data[2] * other[1],
    data[2] * other[0] - data[0] * other[2],
    data[0] * other[1] - data[1] * other[0]
  };
}
