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

void Renderer::triangle(std::array<Vector3f, 3> points, const RGB& color, float *zBuffer) {
  Vector2f min{image.getWidth() - 1, image.getHeight() - 1};
  Vector2f max{0, 0};
  Vector2f bounds = min;

  for (auto& point : points) {
    for (int i = 0; i < 2; i++) {
      min[i] = std::max(0.f, std::min(point[i], min[i]));
      max[i] = std::min(bounds[i], std::max(point[i], max[i]));
    }
  }

  for (int x = min[0]; x <= max[0]; x++) {
    for (int y = min[1]; y <= max[1]; y++) {
      auto u = Vector3f({
          points[1][0] - points[0][0],
          points[2][0] - points[0][0],
          points[0][0] - x
        }).cross({
          points[1][1] - points[0][1],
          points[2][1] - points[0][1],
          points[0][1] - y
        });
      if (abs(u[2]) < 1) {
        continue;
      }

      auto weights = Vector3f({ 1.f - (u[0]+u[1])/u[2], u[0]/u[2], u[1]/u[2] });
      if (weights[0] < 0 || weights[1] < 0 || weights[2] < 0) {
        continue;
      }

      float z = 0;
      for (int i = 0; i < 3; i++) {
        z += weights[i] * points[i][2];
      }

      int zOffset = x + y * image.getWidth();
      if (!zBuffer || zBuffer[zOffset] < z) {
        if (zBuffer) {
          zBuffer[zOffset] = z;
        }
        image.set(x, y, color);
      }
    }
  }
}
