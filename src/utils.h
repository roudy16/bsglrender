#pragma once

#include <cmath>

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

//#include "SDL.h"
//void ColorSurface(SDL_Surface* surface, Color color, float t) {
//    constexpr Color blue = { 0.0f, 0.0f, 1.0f, 1.0f };
//    constexpr Color red = { 1.0f, 0.0f, 0.0f, 1.0f };
//
//    auto colorTransform = [t](Color c) {
//        const float tt = (std::sinf(t * 2.0f * static_cast<float>(M_PI)) + 1.0f) / 2.0f;
//        return c * tt;
//    };
//
//    Uint32 ct = ColorConvert4fU32(colorTransform(color));
//    SDL_FillRect(surface, nullptr, ct);
//}
