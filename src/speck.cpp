#include "ppm.hpp"
#include "renderer.hpp"
#include <fstream>

int main() {
  srand(time(0));
  Renderer render(PPMImage(255, 255));
  for (int i = 0; i < 100; i++) {
    render.line(
        rand() % 256,
        rand() % 256,
        rand() % 256,
        rand() % 256,
        RGB::random()
    );
  }

  std::ofstream file("test.p6", std::ios::binary);
  if (!file.good()) {
    throw std::runtime_error("Couldn't open file");
  }

  render.getImage().write(file);

  file.close();
}
