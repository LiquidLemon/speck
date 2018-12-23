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

  for (auto &face : obj.faces) {
    std::array<Vector2i, 3> coords;

    std::transform(face.begin(), face.end(), coords.begin(),
      [&](int i) -> Vector2i {
        auto& v = obj.vertices[i];
        return {
          static_cast<int>((v[0] + 1) * render.getImage().getWidth() / 2),
          static_cast<int>((v[1] + 1) * render.getImage().getWidth() / 2)
        };
      }
    );
    render.triangle(coords, RGB::random());
  }

  render.getImage().flipVertically();

  std::ofstream output("test.p6", std::ios::binary);
  if (!output.good()) {
    throw std::runtime_error("Couldn't open output");
  }

  render.getImage().write(output);

  output.close();
}
