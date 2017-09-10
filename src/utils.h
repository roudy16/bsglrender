#pragma once

#include <cmath>

namespace bsgl {

struct Color {
    float r, g, b, a;
};

Color operator*(const Color& c, float v) { return { c.r * v, c.g * v, c.b * v, c.a * v }; }

constexpr uint32_t ColorConvert4fU32(Color c) {
    unsigned char r = static_cast<unsigned char>(c.r * 255.f);
    unsigned char g = static_cast<unsigned char>(c.g * 255.f);
    unsigned char b = static_cast<unsigned char>(c.b * 255.f);
    unsigned char a = static_cast<unsigned char>(c.a * 255.f);

    return r << 0
        | g << 8
        | b << 16
        | a << 24;
}

}
