#include "ppm.hpp"

PPMImage::PPMImage(size_t width, size_t height) :
  width(width),
  height(height),
  data(std::make_unique<uint8_t[]>(width * height * 3))
{
}

void PPMImage::set(size_t x, size_t y, uint8_t r, uint8_t g, uint8_t b) {
  size_t pixel = 3 * (x + y * width);
  data[pixel] = r;
  data[pixel + 1] = g;
  data[pixel + 2] = b;
}

void PPMImage::write(std::ostream &stream) {
  stream << "P6\n";
  stream << width << " " << height << " " << 255 << "\n";
  for (size_t i = 0; i < width * height * 3; i++) {
    stream << data[i];
  }
}
