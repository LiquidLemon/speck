#pragma once
#include "ppm.hpp"
#include "color.hpp"
#include "vector.hpp"

class Renderer {
  public:
    Renderer(PPMImage &&image);

    void line(int x1, int y1, int x2, int y2, const RGB &color);
    void triangle(
        std::array<Vector3f, 3>,
        float intensity,
        float *zBuffer,
        std::array<Vector2f, 3>,
        PPMImage&
    );

    PPMImage& getImage();

  protected:
    PPMImage image;
};
