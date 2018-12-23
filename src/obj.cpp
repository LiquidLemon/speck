#include "obj.hpp"

void Obj::read(std::istream& stream) {
  std::string type;
  while (!stream.bad() && !stream.eof()) {
    stream >> type;

    if (type == "v") {
      Vector3f vector;
      stream >> vector[0];
      stream >> vector[1];
      stream >> vector[2];

      vertices.push_back(vector);
    } else if (type == "f") {
      std::array<int, 3> face;
      stream >> face[0];
      stream.ignore(256, ' ');
      stream >> face[1];
      stream.ignore(256, ' ');
      stream >> face[2];
      stream.ignore(256, '\n');

      face[0]--;
      face[1]--;
      face[2]--;
      faces.push_back(face);
    } else {
      stream.ignore(256, '\n');
    }
  }
}
