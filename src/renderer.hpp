#pragma once
#include "ppm.hpp"
#include "color.hpp"

class Renderer {
  public:
    Renderer(PPMImage &&image);

    void line(int x1, int y1, int x2, int y2, const RGB &color);

    PPMImage& getImage();

  protected:
    PPMImage image;
};
