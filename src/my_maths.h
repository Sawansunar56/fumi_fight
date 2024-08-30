#pragma once
#include "types.h"
#include <cmath>

// defines
constexpr f32 Pi32  = 3.14159265359f;
constexpr f32 Tau32 = 6.28318530717958647692f;

union v2 {
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

union v3 {
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

union v4 {
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

union v2d {
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

union v3d {
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

union v4d {
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

union v2i {
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

union v3i {
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

union v4i {
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

#include "my_maths.inl"
