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
      Face face;

      for (int i = 0; i < 3; i++) {
        stream >> face.vertices[i];
        face.vertices[i]--;
        stream.ignore(1);
        stream >> face.uvs[i];
        face.uvs[i]--;
        stream.ignore(1);
        stream >> face.normals[i];
        face.normals[i]--;
      }

      faces.push_back(face);
    } else if (type == "vt") {
      Vector2f vector;
      stream >> vector[0];
      stream >> vector[1];
    } else {
      stream.ignore(256, '\n');
    }
  }
}
