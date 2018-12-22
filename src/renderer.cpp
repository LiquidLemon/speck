#include "renderer.hpp"
#include <cmath>
#include <algorithm>

Renderer::Renderer(PPMImage &&image) :
  image(std::move(image))
{
}

PPMImage& Renderer::getImage() {
  return image;
}

void Renderer::line(int x0, int y0, int x1, int y1, const RGB &color) {
  int width = abs(x1 - x0);
  int height = abs(y1 - y0);
  int steps = std::max(width, height);

  float diff = 1.0 / steps;
  float xdiff = (x1 - x0) * diff;
  float ydiff = (y1 - y0) * diff;

  float x = x0;
  float y = y0;
  for (int i = 0; i < steps; i++) {
    x += xdiff;
    y += ydiff;
    image.set(x, y, color);
  }
}

