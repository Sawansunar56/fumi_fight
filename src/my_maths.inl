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
