#pragma once
#include "types.h"

union v2
{
    struct {
        f32 x, y;
    };

    struct {
        f32 r, g;
    };
    f32 E[2];
};

union v3
{
    struct {
        f32 x, y,z;
    };

    struct {
        f32 r, g, b;
    };
    f32 E[3];
};

union v4
{
    struct {
        f32 x, y,z,w;
    };

    struct {
        f32 r, g, b, a;
    };
    f32 E[4];
};

union v2d
{
    struct {
        f64 x, y;
    };

    struct {
        f64 r, g;
    };
    f64 E[2];
};

union v3d
{
    struct {
        f64 x, y,z;
    };

    struct {
        f64 r, g, b;
    };
    f64 E[3];
};

union v4d
{
    struct {
        f64 x, y,z,w;
    };

    struct {
        f64 r, g, b, a;
    };
    f64 E[4];
};

union v2i
{
    struct {
        i32 x, y;
    };

    struct {
        i32 r, g;
    };
    i32 E[2];
};

union v3i
{
    struct {
        i32 x, y,z;
    };

    struct {
        i32 r, g, b;
    };
    i32 E[3];
};

union v4i
{
    struct {
        i32 x, y,z,w;
    };

    struct {
        i32 r, g, b, a;
    };
    i32 E[4];
};

inline v2 operator+(v2 a, v2 b) {
    v2 result = {};

    result.x = a.x + b.x;
    result.y = a.y + b.y;

    return result;
}

inline v2 operator-(v2 a, v2 b) {
    v2 result = {};

    result.x = a.x - b.x;
    result.y = a.y - b.y;

    return result;
}

inline v2 operator-(v2 a) {
    v2 Result = {};

    Result.x = -a.x;
    Result.y = -a.y;
    
    return Result;
}

inline v2 operator*(v2 a, f32 b)
{
    v2 result = {};

    result.x = a.x * b;
    result.y = a.y * b;

    return result;
}

inline v2 &operator+=(v2 &a, v2 b)
{
    a = a + b;
    return a;
}

inline v2 &operator-=(v2 &a, v2 b)
{
    a = a - b;
    return a;
}

inline v2 &operator*=(v2 &a, f32 b)
{
    a = a * b;
    return a;
}

inline v3 operator+(v3 a, v3 b) {
    v3 result = {};

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;

    return result;
}

inline v3 operator-(v3 a, v3 b) {
    v3 result = {};

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;

    return result;
}

inline v3 operator-(v3 a) {
    v3 Result = {};

    Result.x = -a.x;
    Result.y = -a.y;
    Result.z = -a.z;
    
    return Result;
}

inline v3 operator*(v3 a, f32 b)
{
    v3 result = {};

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;

    return result;
}

inline v3 &operator+=(v3 &a, v3 b)
{
    a = a + b;
    return a;
}

inline v3 &operator-=(v3 &a, v3 b)
{
    a = a - b;
    return a;
}

inline v3 &operator*=(v3 &a, f32 b)
{
    a = a * b;
    return a;
}

inline v4 operator+(v4 a, v4 b) {
    v4 result = {};

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;

    return result;
}

inline v4 operator-(v4 a, v4 b) {
    v4 result = {};

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;

    return result;
}

inline v4 operator-(v4 a) {
    v4 Result = {};

    Result.x = -a.x;
    Result.y = -a.y;
    Result.z = -a.z;
    Result.w = -a.w;
    
    return Result;
}

inline v4 operator*(v4 a, f32 b)
{
    v4 result = {};

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;
    result.w = a.w * b;

    return result;
}

inline v4 &operator+=(v4 &a, v4 b)
{
    a = a + b;
    return a;
}

inline v4 &operator-=(v4 &a, v4 b)
{
    a = a - b;
    return a;
}

inline v4 &operator*=(v4 &a, f32 b)
{
    a = a * b;
    return a;
}
inline v2d operator+(v2d a, v2d b) {
    v2d result = {};

    result.x = a.x + b.x;
    result.y = a.y + b.y;

    return result;
}

inline v2d operator-(v2d a, v2d b) {
    v2d result = {};

    result.x = a.x - b.x;
    result.y = a.y - b.y;

    return result;
}

inline v2d operator-(v2d a) {
    v2d Result = {};

    Result.x = -a.x;
    Result.y = -a.y;
    
    return Result;
}

inline v2d operator*(v2d a, f32 b)
{
    v2d result = {};

    result.x = a.x * b;
    result.y = a.y * b;

    return result;
}

inline v2d &operator+=(v2d &a, v2d b)
{
    a = a + b;
    return a;
}

inline v2d &operator-=(v2d &a, v2d b)
{
    a = a - b;
    return a;
}

inline v2d &operator*=(v2d &a, f32 b)
{
    a = a * b;
    return a;
}

inline v3d operator+(v3d a, v3d b) {
    v3d result = {};

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;

    return result;
}

inline v3d operator-(v3d a, v3d b) {
    v3d result = {};

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;

    return result;
}

inline v3d operator-(v3d a) {
    v3d Result = {};

    Result.x = -a.x;
    Result.y = -a.y;
    Result.z = -a.z;
    
    return Result;
}

inline v3d operator*(v3d a, f32 b)
{
    v3d result = {};

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;

    return result;
}

inline v3d &operator+=(v3d &a, v3d b)
{
    a = a + b;
    return a;
}

inline v3d &operator-=(v3d &a, v3d b)
{
    a = a - b;
    return a;
}

inline v3d &operator*=(v3d &a, f32 b)
{
    a = a * b;
    return a;
}

inline v4d operator+(v4d a, v4d b) {
    v4d result = {};

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;

    return result;
}

inline v4d operator-(v4d a, v4d b) {
    v4d result = {};

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;

    return result;
}

inline v4d operator-(v4d a) {
    v4d Result = {};

    Result.x = -a.x;
    Result.y = -a.y;
    Result.z = -a.z;
    Result.w = -a.w;
    
    return Result;
}

inline v4d operator*(v4d a, f32 b)
{
    v4d result = {};

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;
    result.w = a.w * b;

    return result;
}

inline v4d &operator+=(v4d &a, v4d b)
{
    a = a + b;
    return a;
}

inline v4d &operator-=(v4d &a, v4d b)
{
    a = a - b;
    return a;
}

inline v4d &operator*=(v4d &a, f32 b)
{
    a = a * b;
    return a;
}
inline v2i operator+(v2i a, v2i b) {
    v2i result = {};

    result.x = a.x + b.x;
    result.y = a.y + b.y;

    return result;
}

inline v2i operator-(v2i a, v2i b) {
    v2i result = {};

    result.x = a.x - b.x;
    result.y = a.y - b.y;

    return result;
}

inline v2i operator-(v2i a) {
    v2i Result = {};

    Result.x = -a.x;
    Result.y = -a.y;
    
    return Result;
}

inline v2i operator*(v2i a, f32 b)
{
    v2i result = {};

    result.x = a.x * b;
    result.y = a.y * b;

    return result;
}

inline v2i &operator+=(v2i &a, v2i b)
{
    a = a + b;
    return a;
}

inline v2i &operator-=(v2i &a, v2i b)
{
    a = a - b;
    return a;
}

inline v2i &operator*=(v2i &a, f32 b)
{
    a = a * b;
    return a;
}

inline v3i operator+(v3i a, v3i b) {
    v3i result = {};

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;

    return result;
}

inline v3i operator-(v3i a, v3i b) {
    v3i result = {};

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;

    return result;
}

inline v3i operator-(v3i a) {
    v3i Result = {};

    Result.x = -a.x;
    Result.y = -a.y;
    Result.z = -a.z;
    
    return Result;
}

inline v3i operator*(v3i a, f32 b)
{
    v3i result = {};

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;

    return result;
}

inline v3i &operator+=(v3i &a, v3i b)
{
    a = a + b;
    return a;
}

inline v3i &operator-=(v3i &a, v3i b)
{
    a = a - b;
    return a;
}

inline v3i &operator*=(v3i &a, f32 b)
{
    a = a * b;
    return a;
}

inline v4i operator+(v4i a, v4i b) {
    v4i result = {};

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;

    return result;
}

inline v4i operator-(v4i a, v4i b) {
    v4i result = {};

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;

    return result;
}

inline v4i operator-(v4i a) {
    v4i Result = {};

    Result.x = -a.x;
    Result.y = -a.y;
    Result.z = -a.z;
    Result.w = -a.w;
    
    return Result;
}

inline v4i operator*(v4i a, f32 b)
{
    v4i result = {};

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;
    result.w = a.w * b;

    return result;
}

inline v4i &operator+=(v4i &a, v4i b)
{
    a = a + b;
    return a;
}

inline v4i &operator-=(v4i &a, v4i b)
{
    a = a - b;
    return a;
}

inline v4i &operator*=(v4i &a, f32 b)
{
    a = a * b;
    return a;
}
