#include "color.hpp"

RGB::RGB(uint8_t r, uint8_t g, uint8_t b) :
  r(r),
  g(g),
  b(b)
{
};

const RGB RGB::red = RGB(255, 0, 0);
const RGB RGB::green = RGB(0, 255, 0);
const RGB RGB::blue = RGB(0, 0, 255);
const RGB RGB::black = RGB(0, 0, 0);
const RGB RGB::white = RGB(255, 255, 255);
