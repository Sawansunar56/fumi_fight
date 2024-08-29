#pragma once
#include "my_maths.h"

struct Vertex 
{
    v3 position;
    v4 color;
};

typedef v4 color;
typedef v4 hsl_color;

inline color normalize_color(color Color)
{
    color Result = Color / 255.0f;
    return Result;
}

// Helper function to clamp values between 0 and 1
inline f32 clamp(f32 value, f32 min = 0.0f, f32 max = 1.0f)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

inline v4 normalize_hsl(hsl_color color)
{
   v4 Result = {};
    // Normalize hue to range [0, 1]
    color.h = fmod(color.h, 360.0f) / 360.0f;
    // Normalize other components
    color.s = color.s / 100.0f;
    color.l = color.l / 100.0f;

    // Calculate chroma
    f32 c = (1.0f - std::fabs(2.0f * color.l - 1.0f)) * color.s;
    f32 x = c * (1.0f - std::fabs(fmod(color.h * 6.0f, 2.0f) - 1.0f));
    f32 m = color.l - c / 2.0f;

    f32 r1, g1, b1;
    if (0 <= color.h && color.h < 1.0f / 6.0f)
    {
        r1 = c;
        g1 = x;
        b1 = 0;
    }
    else if (1.0f / 6.0f <= color.h && color.h < 2.0f / 6.0f)
    {
        r1 = x;
        g1 = c;
        b1 = 0;
    }
    else if (2.0f / 6.0f <= color.h && color.h < 3.0f / 6.0f)
    {
        r1 = 0;
        g1 = c;
        b1 = x;
    }
    else if (3.0f / 6.0f <= color.h && color.h < 4.0f / 6.0f)
    {
        r1 = 0;
        g1 = x;
        b1 = c;
    }
    else if (4.0f / 6.0f <= color.h && color.h < 5.0f / 6.0f)
    {
        r1 = x;
        g1 = 0;
        b1 = c;
    }
    else
    {
        r1 = c;
        g1 = 0;
        b1 = x;
    }

    Result.r = clamp(r1 + m);
    Result.g = clamp(g1 + m);
    Result.b = clamp(b1 + m);
    Result.a = 1.0f;

    return Result;
}

