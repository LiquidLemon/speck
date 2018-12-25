#include "ppm.hpp"
#include <cassert>

PPMImage::PPMImage(size_t width, size_t height) :
  width(width),
  height(height),
  data(std::make_unique<uint8_t[]>(width * height * 3))
{
}

PPMImage::PPMImage(PPMImage &&other) {
  width = other.width;
  height = other.height;
  data = std::move(other.data);
}

size_t PPMImage::getWidth() const {
  return width;
}
size_t PPMImage::getHeight() const {
  return height;
}

void PPMImage::flipVertically() {
  for (int y = 0; y < height / 2; y++) {
    for (int x = 0; x < width; x++) {
      std::swap(data[3 * (x + y * width)], data[3 * (x + (height - y - 1) * width)]);
      std::swap(data[3 * (x + y * width) + 1], data[3 * (x + (height - y - 1) * width) + 1]);
      std::swap(data[3 * (x + y * width) + 2], data[3 * (x + (height - y - 1) * width) + 2]);
    }
  }
}

void PPMImage::set(size_t x, size_t y, const RGB& color) {
  size_t pixel = 3 * (x + y * width);
  data[pixel] = color.r;
  data[pixel + 1] = color.g;
  data[pixel + 2] = color.b;
}

void PPMImage::write(std::ostream &stream) {
  stream << "P6\n";
  stream << width << " " << height << " " << 255 << "\n";
  for (size_t i = 0; i < width * height * 3; i++) {
    stream << data[i];
  }
}

PPMImage PPMImage::loadP6(std::istream& stream) {
  std::string type;
  stream >> type;
  assert(type == "P6");
  int width, height;
  stream >> width >> height;

  PPMImage img(width, height);
  stream.ignore(1);
  for (int i = 0; i < width * height * 3; i++) {
    stream >> img.data[i];
  }

  return img;
}

