#include "ppm.hpp"
#include <fstream>

int main() {
  PPMImage image(256, 256);
  for (int y = 0; y < 256; y++) {
    for (int x = 0; x < 256; x++) {
      image.set(x, y, x, y, (x + y) % 256);
    }
  }

  std::ofstream file("test.p6", std::ios::binary);
  if (!file.good()) {
    throw std::runtime_error("Couldn't open file");
  }

  image.write(file);

  file.close();
}
