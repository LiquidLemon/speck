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

void Renderer::triangle(std::array<Vector2i, 3> points, const RGB& color) {
  std::sort(points.begin(), points.end(), [](auto& a, auto& b) { return a[1] < b[1]; });

  auto& a = points[0];
  auto& b = points[1];
  auto& c = points[2];
  float dx0 = static_cast<float>(b[0] - a[0]) / (b[1] - a[1]);
  float dx1 = static_cast<float>(c[0] - a[0]) / (c[1] - a[1]);
  float x0 = a[0];
  float x1 = a[0];
  for (int y = a[1]; y < b[1]; y++) {
    line(x0, y, x1, y, color);
    x0 += dx0;
    x1 += dx1;
  }

  dx0 = static_cast<float>(c[0] - b[0]) / (c[1] - b[1]);
  x0 = b[0];
  for (int y = b[1]; y <= c[1]; y++) {
    line(x0, y, x1, y, color);
    x0 += dx0;
    x1 += dx1;
  }
}
