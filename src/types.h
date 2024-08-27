#pragma once

typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;

typedef char      int8;
typedef short     int16;
typedef int       int32;
typedef long long int64;

typedef uint8  u8;
typedef uint16 u16;
typedef uint32 u32;
typedef uint64 u64;

typedef int8  i8;
typedef int16 i16;
typedef int32 i32;
typedef int64 i64;

typedef i8  s8;
typedef i16 s16;
typedef i32 s32;
typedef i64 s64;

typedef s8  b8;
typedef s32 b32;

typedef float  f32;
typedef double f64;

#define internals     static
#define global_var    static
#define local_persist static

static_assert(sizeof(u8)  == 1, "u8 is not 8 bit");
static_assert(sizeof(u16) == 2, "u16 is not 16 bit");
static_assert(sizeof(u32) == 4, "u32 is not 32 bit");
static_assert(sizeof(u64) == 8, "u64 is not 64 bit");

static_assert(sizeof(s8)  == 1, "s8 is not 8 bit");
static_assert(sizeof(s16) == 2, "s8 is not 16 bit");
static_assert(sizeof(s32) == 4, "s8 is not 32 bit");
static_assert(sizeof(s64) == 8, "s8 is not 64 bit");

static_assert(sizeof(f32) == 4, "f32 is not 32 bit");
static_assert(sizeof(f64) == 8, "f64 is not 64 bit");

