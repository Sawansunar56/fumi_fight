#pragma once
#include "types.h"
#include <cmath>

// defines
constexpr f32 Pi32  = 3.14159265359f;
constexpr f32 Tau32 = 6.28318530717958647692f;


union v2f32 {
    struct
    {
        f32 x, y;
    };

    struct
    {
        f32 r, g;
    };
    f32 E[2];
};

union v3f32 {
    struct
    {
        f32 x, y, z;
    };

    struct
    {
        f32 r, g, b;
    };
    f32 E[3];
};

union v4f32 {
    struct
    {
        f32 x, y, z, w;
    };

    struct
    {
        f32 r, g, b, a;
    };

    struct
    {
        f32 h, s, l, alpha;
    };

    f32 E[4];
};

union v2f64 {
    struct
    {
        f64 x, y;
    };

    struct
    {
        f64 r, g;
    };
    f64 E[2];
};

union v3f64 {
    struct
    {
        f64 x, y, z;
    };

    struct
    {
        f64 r, g, b;
    };
    f64 E[3];
};

union v4f64 {
    struct
    {
        f64 x, y, z, w;
    };

    struct
    {
        f64 r, g, b, a;
    };
    f64 E[4];
};

union v2i32 {
    struct
    {
        i32 x, y;
    };

    struct
    {
        i32 r, g;
    };
    i32 E[2];
};

union v3i32 {
    struct
    {
        i32 x, y, z;
    };

    struct
    {
        i32 r, g, b;
    };
    i32 E[3];
};

union v4i32 {
    struct
    {
        i32 x, y, z, w;
    };

    struct
    {
        i32 r, g, b, a;
    };
    i32 E[4];
};

union mat4x4 {
    f32 E[4][4];

    f32* operator[](i32 index) {
        return E[index];
    }

    const f32* operator[](i32 index) const {
        return E[index];
    }
};

union v2i16 {
    struct {
        i16 x, y;
    };
    i16 E[2];
};

union v3i16 {
    struct {
        i16 x, y, z;
    };
    i16 E[3];
};

union v4i16 {
    struct {
        i16 x, y, z, w;
    };
    i16 E[4];
};

union v2i64 {
    struct {
        i64 x, y;
    };
    i64 E[2];
};

union v3i64 {
    struct {
        i64 x, y, z;
    };
    i64 E[3];
};

union v4i64 {
    struct {
        i64 x, y, z, w;
    };
    i64 E[4];
};

typedef v2f32 v2;
typedef v3f32 v3;
typedef v4f32 v4;

typedef v2f64 v2d;
typedef v3f64 v3d;
typedef v4f64 v4d;

typedef v2i32 v2i;
typedef v3i32 v3i;
typedef v4i32 v4i;

typedef v4 color;
typedef v4 hsl_color;

#include "my_maths.inl"
