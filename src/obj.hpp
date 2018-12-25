#pragma once
#include <istream>
#include <vector>
#include <array>
#include "vector.hpp"

struct Face {
  std::array<int, 3> vertices;
  std::array<int, 3> uvs;
  std::array<int, 3> normals;
};

class Obj {
  public:
    Obj() = default;
    ~Obj() = default;

    void read(std::istream& stream);

    std::vector<Vector3f> vertices;
    std::vector<Vector2f> uvs;
    std::vector<Face> faces;
};
