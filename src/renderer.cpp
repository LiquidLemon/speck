#include "renderer.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

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

  int transposed = false;
  if (width < height) {
    std::swap(x0, y0);
    std::swap(x1, y1);
    std::swap(width, height);
    transposed = true;
  }

  if (x0 > x1) {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }

  int error = 0;
  int y = y0;
  int dy = y0 < y1 ? 1 : -1;
  for (int x = x0; x <= x1; x++) {
    if (transposed) {
      image.set(y, x, color);
    } else {
      image.set(x, y, color);
    }

    error += height * 2;
    if (error > width) {
      y += dy;
      error -= 2 * width;
    }
  }
}

