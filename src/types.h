#pragma once
#include <cstdint>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef i8 s8;
typedef i16 s16;
typedef i32 s32;
typedef i64 s64;

typedef i8 b8;
typedef i16 b16;
typedef i32 b32;
typedef i64 b64;

typedef float f32;
typedef double f64;

typedef uintptr_t umm;
typedef intptr_t  smm;

#define function static
#define glob static
#define locals static

static_assert(sizeof(u8) == 1, "u8  is not 8  bit");
static_assert(sizeof(u16) == 2, "u16 is not 16 bit");
static_assert(sizeof(u32) == 4, "u32 is not 32 bit");
static_assert(sizeof(u64) == 8, "u64 is not 64 bit");

static_assert(sizeof(s8) == 1, "s8  is not 8  bit");
static_assert(sizeof(s16) == 2, "s16 is not 16 bit");
static_assert(sizeof(s32) == 4, "s32 is not 32 bit");
static_assert(sizeof(s64) == 8, "s64 is not 64 bit");

static_assert(sizeof(f32) == 4, "f32 is not 32 bit");
static_assert(sizeof(f64) == 8, "f64 is not 64 bit");

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))

constexpr s8 MIN_S8   = (s8)0x80;
constexpr s16 MIN_S16 = (s16)0x8000;
constexpr s32 MIN_S32 = (s32)0x80000000;
constexpr s64 MIN_S64 = (s64)0x8000000000000000llu;

constexpr s8 MAX_S8   = (s8)0x7f;
constexpr s16 MAX_S16 = (s16)0x7fff;
constexpr s32 MAX_S32 = (s32)0x7fffffff;
constexpr s64 MAX_S64 = (s64)0x7fffffffffffffffllu;

constexpr u8 MAX_U8   = 0xff;
constexpr u16 MAX_U16 = 0xffff;
constexpr u32 MAX_U32 = 0xffffffff;
constexpr u64 MAX_U64 = 0xffffffffffffffff;

#if NDEBUG
#if _MSC_VER
#include <cstdio>
#define Assert(Expression, ...)                                                \
    if (!(Expression))                                                         \
    {                                                                          \
        printf("[ASSERT]: %s, file %s, line %d, \n[ERROR MSG] %s\n",           \
               #Expression,                                                    \
               __FILE__,                                                       \
               __LINE__,                                                       \
               __VA_ARGS__);                                                   \
        __debugbreak();                                                        \
    }
#else
#include <cstdio>
#include <signal.h>
#define Assert(Expression, ...)                                                \
    if (!(Expression))                                                         \
    {                                                                          \
        printf("[ASSERT]: %s, file %s, line %d, \n[ERROR MSG] %s\n",           \
               #Expression,                                                    \
               __FILE__,                                                       \
               __LINE__,                                                       \
               __VA_ARGS__);                                                   \
        raise(SIGTRAP)                                                         \
    }
#endif
#else
#define Assert(Expression, ...)
#endif
