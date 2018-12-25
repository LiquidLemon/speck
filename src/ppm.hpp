#pragma once
#include <cstdlib>
#include <cstdint>
#include <memory>
#include <iostream>

#include "color.hpp"

class PPMImage {
  public:
    PPMImage(size_t width, size_t height);
    PPMImage(PPMImage &&other);
    ~PPMImage() = default;

    static PPMImage loadP6(std::istream& stream);
    void set(size_t x, size_t y, const RGB &color);
    RGB get(int x, int y) const;
    void write(std::ostream &stream);
    void flipVertically();

    size_t getWidth() const;
    size_t getHeight() const;

  protected:
    size_t width;
    size_t height;
    std::unique_ptr<uint8_t[]> data;
};
