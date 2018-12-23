#pragma once
#include <istream>
#include <vector>
#include <array>
#include "vector.hpp"

class Obj {
  public:
    Obj() = default;
    ~Obj() = default;

    void read(std::istream& stream);

    std::vector<Vector3f> vertices;
    std::vector<std::array<int, 3>> faces;
};
