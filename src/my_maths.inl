
inline v2 operator+(v2 a, v2 b)
{
    v2 result = {};

    result.x = a.x + b.x;
    result.y = a.y + b.y;

    return result;
}

inline v2 operator-(v2 a, v2 b)
{
    v2 result = {};

    result.x = a.x - b.x;
    result.y = a.y - b.y;

    return result;
}

inline v2 operator-(v2 a)
{
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

inline v3 operator+(v3 a, v3 b)
{
    v3 result = {};

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;

    return result;
}

inline v3 operator-(v3 a, v3 b)
{
    v3 result = {};

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;

    return result;
}

inline v3 operator-(v3 a)
{
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

inline v4 operator+(v4 a, v4 b)
{
    v4 result = {};

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;

    return result;
}

inline v4 operator-(v4 a, v4 b)
{
    v4 result = {};

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;

    return result;
}

inline v4 operator-(v4 a)
{
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

inline v4 operator/(v4 a, f32 b)
{
    v4 Result = {};

    Result.x = a.x / b;
    Result.y = a.y / b;
    Result.z = a.z / b;
    Result.w = a.w / b;

    return Result;
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
inline v2d operator+(v2d a, v2d b)
{
    v2d result = {};

    result.x = a.x + b.x;
    result.y = a.y + b.y;

    return result;
}

inline v2d operator-(v2d a, v2d b)
{
    v2d result = {};

    result.x = a.x - b.x;
    result.y = a.y - b.y;

    return result;
}

inline v2d operator-(v2d a)
{
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

inline v3d operator+(v3d a, v3d b)
{
    v3d result = {};

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;

    return result;
}

inline v3d operator-(v3d a, v3d b)
{
    v3d result = {};

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;

    return result;
}

inline v3d operator-(v3d a)
{
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

inline v4d operator+(v4d a, v4d b)
{
    v4d result = {};

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;

    return result;
}

inline v4d operator-(v4d a, v4d b)
{
    v4d result = {};

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;

    return result;
}

inline v4d operator-(v4d a)
{
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
inline v2i operator+(v2i a, v2i b)
{
    v2i result = {};

    result.x = a.x + b.x;
    result.y = a.y + b.y;

    return result;
}

inline v2i operator-(v2i a, v2i b)
{
    v2i result = {};

    result.x = a.x - b.x;
    result.y = a.y - b.y;

    return result;
}

inline v2i operator-(v2i a)
{
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

inline v3i operator+(v3i a, v3i b)
{
    v3i result = {};

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;

    return result;
}

inline v3i operator-(v3i a, v3i b)
{
    v3i result = {};

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;

    return result;
}

inline v3i operator-(v3i a)
{
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

inline v4i operator+(v4i a, v4i b)
{
    v4i result = {};

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;

    return result;
}

inline v4i operator-(v4i a, v4i b)
{
    v4i result = {};

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;

    return result;
}

inline v4i operator-(v4i a)
{
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

inline mat4x4 create_projection_mat(f32 fov, f32 aspect, f32 near, f32 far)
{
    mat4x4 Result = {};

    f32 half_fov = tanf(fov / 2.0f);
    Result[0][0] = 1.0f / (aspect * half_fov);
    Result[1][1] = 1.0f / (half_fov);
    Result[2][2] = -(far + near) / (far - near);

    Result[2][3] = -1.0f;
    Result[3][2] = -(2.0f * far * near) / (far - near);

    return Result;
}

inline mat4x4 create_orthographic_mat(f32 left,
                                      f32 right,
                                      f32 bottom,
                                      f32 top,
                                      f32 near,
                                      f32 far)
{
    // 0  -> x set
    // 1 -> y set
    // 2 -> z set
    // 3 -> everything set except z
    mat4x4 result = {};

    result[0][0] = 2.0f / (right - left);
    result[1][1] = 2.0f / (top - bottom);
    result[2][2] = -2.0f / (far - near);
    result[3][0] = -(right + left) / (right - left);
    result[3][1] = -(top + bottom) / (top - bottom);
    result[3][2] = -(far + near) / (far - near);
    result[3][3] = 1.0f;

    return result;
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

inline color normalize_color(color Color)
{
    color Result = Color / 255.0f;
    return Result;
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

inline color hsl_to_rgb(hsl_color Color)
{
    color Result = normalize_hsl(Color);

    Result *= 255.0f;

    return Result;
}
