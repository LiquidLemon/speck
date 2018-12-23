#pragma once
#include <cstdint>

class RGB {
  public:
    uint8_t r, g, b;
    RGB(uint8_t r, uint8_t g, uint8_t b);
    RGB(uint8_t w);
    ~RGB() = default;

    static RGB random();

    static const RGB red;
    static const RGB green;
    static const RGB blue;
    static const RGB black;
    static const RGB white;
};

