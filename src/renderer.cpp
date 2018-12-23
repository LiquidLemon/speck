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

  int xerror = 0;
  int yerror = 0;
  int dx = x0 < x1 ? 1 : -1;
  int dy = y0 < y1 ? 1 : -1;

  int x = x0;
  int y = y0;
  for (int i = 0; i < steps; i++) {
    image.set(x, y, color);
    xerror += width * 2;
    if (xerror > height) {
      x += dx;
      xerror -= height * 2;
    }
    yerror += height * 2;
    if (yerror > width) {
      y += dy;
      yerror -= width * 2;
    }
  }
}

