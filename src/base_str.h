#pragma once
#include "types.h"
#include "arena.h"

typedef struct Str8 Str8;
struct Str8
{
 u8 *data;
 u64 size;
};

typedef struct Str16 Str16;
struct Str16
{
 u16 *data;
 u64 size;
};

typedef struct Str32 Str32;
struct Str32
{
 u32 *data;
 u64 size;
};

typedef struct Str8Node Str8Node;
struct Str8Node
{
 Str8Node *next;
 Str8 string;
};

typedef struct Str8List Str8List;
struct Str8List
{
 Str8Node *first;
 Str8Node *last;
 u64 count;
 u64 size;
};

typedef struct Str8Array Str8Array;
struct Str8Array
{
 Str8 *v;
 u64 count;
};

typedef u32 MatchFlags;
enum
{
 MatchFlag_CaseInsensitive  = (1 << 0),
 MatchFlag_RightSideSloppy  = (1 << 1),
 MatchFlag_SlashInsensitive = (1 << 2),
 MatchFlag_FindLast         = (1 << 3),
 MatchFlag_KeepEmpties      = (1 << 4),
};

// builder
Str8 make_str8(char *c);
Str8 make_str8x(u8 *str, u64 size);
Str16 make_str16(u16 *c);
Str16 make_str16x(u16 *c, u64 size);
Str32 make_str32(u32 *c);
Str32 make_str32x(u32 *c, u64 size);

Str8 make_str8_from_s8(Arena* arena,  s8 value);
Str8 make_str8_from_s16(Arena* arena, s16 value);
Str8 make_str8_from_s32(Arena* arena, s32 value);
Str8 make_str8_from_s64(Arena* arena, s64 value);

#define make_str8_lit(S) make_str8x((u8 *)(S), sizeof(S) - 1)

#define MAKE_STR8_FROM_NUMBERS_DEF(type, fmt) \
Str8 make_str8_from_##type(Arena* arena, type value);

#define MAKE_STR8_FROM_NUMBERS_IMPL(type, fmt) \
Str8 make_str8_from_##type(Arena* arena, type value) { \
  u8 *buffer = PushArray(arena, 32, u8); \
  s32 len = snprintf((char *)buffer, 32, fmt, value); \
  return make_str8x(buffer, (u64)len); \
}

#define CONCATE_STR_DEF(type, func_name) \
type concate_str##func_name(Arena* arena, type x, type y);

#define CONCATE_STR_IMPL(type, func_name) \
type concate_str##func_name(Arena* arena, type x, type y) \
{ \
  u64 total_size = x.size + y.size; \
  u##func_name *data       = PushArray(arena, total_size, u##func_name); \
  MemoryCopy(data, x.data, x.size); \
  MemoryCopy(data + x.size, y.data, y.size); \
  return make_str##func_name##x(data, total_size); \
}

MAKE_STR8_FROM_NUMBERS_DEF(s8, "%d")
MAKE_STR8_FROM_NUMBERS_DEF(s16, "%d")
MAKE_STR8_FROM_NUMBERS_DEF(s32, "%d")
MAKE_STR8_FROM_NUMBERS_DEF(s64, "%lld")
MAKE_STR8_FROM_NUMBERS_DEF(u8, "%u")
MAKE_STR8_FROM_NUMBERS_DEF(u16, "%u")
MAKE_STR8_FROM_NUMBERS_DEF(u32, "%u")
MAKE_STR8_FROM_NUMBERS_DEF(u64, "%llu")

CONCATE_STR_DEF(Str8, 8)
CONCATE_STR_DEF(Str16, 16)
CONCATE_STR_DEF(Str32, 32)

// print 
void print_str8(Str8 s);
void println_str8(Str8 s);

// length
u64 str8_len(u8 *c);
u64 str16_len(u16 *c);
u64 str32_len(u32 *c);

// data structure manipulations
Str8Node *str8_list_push_node(Str8List *list, Str8Node *node);
Str8Node *str8_list_push(Arena *arena, Str8List *list, Str8 string);

// character state
b32 char_is_space(u8 c);
b32 char_is_upper(u8 c);
b32 char_is_lower(u8 c);
b32 char_is_alpha(u8 c);
b32 char_is_slash(u8 c);
b32 char_is_number(u8 c);

// character conversion
u8 char_to_correct_slash(u8 c);
u8 char_to_upper(u8 c);
u8 char_to_lower(u8 c);

// Pushing
Str8 push_str8fv(Arena *arena, char *fmt, va_list args);
Str8 push_str8f(Arena *arena, char *fmt, ...);

// match and find
u64 find_sub_str8(Str8 string,
                  Str8 substr,
                  u64 start,
                  MatchFlags probably_flags);
Str8 str8_skip(Str8 str, u64 min);

Str8 sub_str8(Str8 string, u64 min, u64 max);
b8 str8_match(Str8 a, Str8 b, MatchFlags flags);
