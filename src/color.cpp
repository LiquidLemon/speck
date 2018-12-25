#include "color.hpp"
#include <cstdlib>

RGB::RGB(uint8_t r, uint8_t g, uint8_t b) :
  r(r),
  g(g),
  b(b)
{
}

RGB::RGB(uint8_t w) :
  r(w),
  g(w),
  b(w)
{
}

RGB RGB::random() {
  return RGB(rand() % 256, rand() % 256, rand() % 256);
}

RGB RGB::operator*(float factor) const {
  return RGB(r * factor, g * factor, b * factor);
}

const RGB RGB::red = RGB(255, 0, 0);
const RGB RGB::green = RGB(0, 255, 0);
const RGB RGB::blue = RGB(0, 0, 255);
const RGB RGB::black = RGB(0, 0, 0);
const RGB RGB::white = RGB(255, 255, 255);
