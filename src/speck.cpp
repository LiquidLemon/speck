#include <fstream>
#include "ppm.hpp"
#include "renderer.hpp"
#include "obj.hpp"

#include <iostream>

int main() {
  srand(time(0));
  Renderer render(PPMImage(1000, 1000));

  std::ifstream head("obj/african_head.obj");
  if (!head.good()) {
    throw std::runtime_error("Failed opening .obj");
  }

  Obj obj;
  obj.read(head);
  head.close();

  for (auto &face : obj.faces) {
    for (int i = 0; i < 3; i++) {
      auto& v0 = obj.vertices[face[i]];
      auto& v1 = obj.vertices[face[(i+1) % 3]];

      int x0 = (v0[0] + 1) * render.getImage().getWidth() / 2;
      int y0 = (-v0[1] + 1) * render.getImage().getHeight() / 2;

      int x1 = (v1[0] + 1) * render.getImage().getWidth() / 2;
      int y1 = (-v1[1] + 1) * render.getImage().getHeight() / 2;
      render.line(x0, y0, x1, y1, RGB::white);
    }
  }

  std::ofstream output("test.p6", std::ios::binary);
  if (!output.good()) {
    throw std::runtime_error("Couldn't open output");
  }

  render.getImage().write(output);

  output.close();
}
