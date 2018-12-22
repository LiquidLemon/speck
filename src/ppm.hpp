#pragma once
#include <cstdlib>
#include <cstdint>
#include <memory>
#include <ostream>

class PPMImage {
  public:
    PPMImage(size_t width, size_t height);
    ~PPMImage() = default;

    void set(size_t x, size_t y, uint8_t r, uint8_t g, uint8_t b);
    void write(std::ostream &stream);

    size_t getWidth() const;
    size_t getHeight() const;

  protected:
    size_t width;
    size_t height;
    std::unique_ptr<uint8_t[]> data;
};
