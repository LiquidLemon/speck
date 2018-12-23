#include <fstream>
#include "ppm.hpp"
#include "renderer.hpp"
#include "obj.hpp"
#include <algorithm>

#include <iostream>

int main() {
  srand(time(0));
  Renderer render(PPMImage(1024, 1024));

  std::ifstream head("obj/african_head.obj");
  if (!head.good()) {
    throw std::runtime_error("Failed opening .obj");
  }

  Obj obj;
  obj.read(head);
  head.close();

  Vector3f light({ 0, 0, 1 });

  for (auto &face : obj.faces) {
    std::array<Vector3f, 3> worldCoords;

    std::transform(face.begin(), face.end(), worldCoords.begin(),
      [&](int i) -> Vector3f { return obj.vertices[i]; }
    );

    std::array<Vector2i, 3> screenCoords;
    std::transform(worldCoords.begin(), worldCoords.end(), screenCoords.begin(),
      [&](auto& v) -> Vector2i {
        return {
          (1 + v[0]) * render.getImage().getWidth() / 2,
          (1 + v[1]) * render.getImage().getHeight() / 2
        };
      }
    );

    auto normal = (worldCoords[0] - worldCoords[1])^(worldCoords[0] - worldCoords[2]);
    normal.normalize();
    float intensity = light * normal;
    if (intensity > 0) {
      render.triangle(screenCoords, RGB(intensity * 255));
    }
  }

  render.getImage().flipVertically();

  std::ofstream output("test.p6", std::ios::binary);
  if (!output.good()) {
    throw std::runtime_error("Couldn't open output");
  }

  render.getImage().write(output);

  output.close();
}
