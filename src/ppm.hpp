#pragma once
#include <cstdlib>
#include <cstdint>
#include <memory>
#include <ostream>

#include "color.hpp"

class PPMImage {
  public:
    PPMImage(size_t width, size_t height);
    PPMImage(PPMImage &&other);
    ~PPMImage() = default;

    void set(size_t x, size_t y, const RGB &color);
    void write(std::ostream &stream);

    size_t getWidth() const;
    size_t getHeight() const;

  protected:
    size_t width;
    size_t height;
    std::unique_ptr<uint8_t[]> data;
};
