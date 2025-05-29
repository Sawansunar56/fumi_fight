#include "base_str.h"
#include "stdarg.h"
#include <arena.h>
#include <cstdio>

#define STB_SPRINTF_DECORATE(name) sown_##name
#include "stb_sprintf.h"

Str8 make_str8(char *c)
{
  Str8 Result = {(u8 *)c, str8_len((u8 *)c)};
  return Result;
}

Str8 make_str8x(u8 *str, u64 size)
{
  Str8 Result = {str, size};
  return Result;
}

Str16 make_str16(u16 *c)
{
  Str16 Result = {(u16 *)c, str16_len((u16 *)c)};
  return Result;
}

Str16 make_str16x(u16 *c, u64 size)
{
  Str16 Result = {c, size};
  return Result;
}

Str32 make_str32(u32 *c)
{
  Str32 Result = {(u32 *)c, str32_len((u32 *)c)};
  return Result;
}

Str32 make_str32x(u32 *c, u64 size)
{
  Str32 Result = {c, size};
  return Result;
}

void print_str8(Str8 s) { printf("%.*s", (int)s.size, s.data); }
void println_str8(Str8 s) { printf("%.*s\n", (int)s.size, s.data); }

MAKE_STR8_FROM_NUMBERS(s8, "%d")
MAKE_STR8_FROM_NUMBERS(s16, "%d")
MAKE_STR8_FROM_NUMBERS(s32, "%d")
MAKE_STR8_FROM_NUMBERS(s64, "%lld")
MAKE_STR8_FROM_NUMBERS(u8, "%u")
MAKE_STR8_FROM_NUMBERS(u16, "%u")
MAKE_STR8_FROM_NUMBERS(u32, "%u")
MAKE_STR8_FROM_NUMBERS(u64, "%llu")

CONCATE_STR(Str8, 8)
CONCATE_STR(Str16, 16)
CONCATE_STR(Str32, 32)

// Str8 concate_str8(Arena *arena, Str8 x, Str8 y)
// {
//   u64 total_size = x.size + y.size;
//   u8 *data       = PushArray(arena, total_size, u8);
//
//   MemoryCopy(data, x.data, x.size);
//   MemoryCopy(data + x.size, y.data, y.size);
//
//   return make_str8x(data, total_size);
// }

u64 str8_len(u8 *c)
{
  u8 *p = c;
  for (; *p != 0; p += 1)
    ;
  return (p - c);
}

u64 str16_len(u16 *c)
{
  u16 *p = c;
  for (; *p != 0; p += 1)
    ;
  return (p - c);
}

u64 str32_len(u32 *c)
{
  u32 *p = c;
  for (; *p != 0; p += 1)
    ;
  return (p - c);
}

Str8Node *str8_list_push_node(Str8List *list, Str8Node *node)
{
  SLLQueuePush(list->first, list->last, node);
  list->count += 1;
  list->size += node->string.size;
  return node;
}

Str8Node *str8_list_push(Arena *arena, Str8List *list, Str8 string)
{
  Str8Node *Result = ZeroPushStruct(arena, Str8Node);
  Result           = str8_list_push_node(list, Result);
  Result->string   = string;

  return Result;
}

b32 char_is_space(u8 c)
{
  return (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\f' ||
          c == '\v');
}

b32 char_is_upper(u8 c) { return ('A' <= c && c <= 'Z'); }
b32 char_is_lower(u8 c) { return ('a' <= c && c <= 'z'); }
b32 char_is_alpha(u8 c) { return (char_is_upper(c) || char_is_lower(c)); }
b32 char_is_slash(u8 c) { return (c == '/' || c == '\\'); }

b32 char_is_number(u8 c) { return ('0' <= c && c <= '9'); }

u8 char_to_lower(u8 c)
{
  if (char_is_upper(c))
  {
    c += ('a' - 'A');
  }
  return (c);
}

u8 char_to_upper(u8 c)
{
  if (char_is_lower(c))
  {
    c += ('A' - 'a');
  }
  return (c);
}

u8 char_to_correct_slash(u8 c)
{
  if (char_is_slash(c))
  {
    c = '/';
  }
  return (c);
}

Str8 push_str8fv(Arena *arena, char *fmt, va_list args)
{
  va_list args2;
  va_copy(args2, args);
  u64 needed_bytes = sown_vsnprintf(0, 0, fmt, args) + 1;
  Str8 result      = {0};
  result.data      = PushArray(arena, needed_bytes, u8);
  // result.str       = PushArrayNoZero(arena, U8, needed_bytes);
  result.size = needed_bytes - 1;
  sown_vsnprintf((char *)result.data, needed_bytes, fmt, args2);
  return result;
}

Str8 push_str8f(Arena *arena, char *fmt, ...)
{
  Str8 result = {0};
  va_list args;
  va_start(args, fmt);
  result = push_str8fv(arena, fmt, args);
  va_end(args);
  return result;
}

Str8 sub_str8(Str8 string, u64 min, u64 max)
{
  if (max > string.size)
  {
    max = string.size;
  }
  if (min > string.size)
  {
    min = string.size;
  }

  if (min > max)
  {
    u64 swap = min;
    min      = max;
    max      = swap;
  }
  string.size = max - min;
  string.data += min;
  return string;
}

b8 str8_match(Str8 a, Str8 b, MatchFlags flags)
{
  b8 result = 0;
  if (a.size == b.size || flags & MatchFlag_RightSideSloppy)
  {
    result = 1;
    for (u64 i = 0; i < a.size; i += 1)
    {
      b8 match = (a.data[i] == b.data[i]);
      if (flags & MatchFlag_CaseInsensitive)
      {
        match |= (char_to_lower(a.data[i]) == char_to_lower(b.data[i]));
      }
      if (flags & MatchFlag_SlashInsensitive)
      {
        match |= (char_to_correct_slash(a.data[i]) ==
                  char_to_correct_slash(b.data[i]));
      }
      if (match == 0)
      {
        result = 0;
        break;
      }
    }
  }
  return result;
}

u64 find_sub_str8(Str8 string, Str8 substr, u64 start, MatchFlags flags)
{
  b8 found      = 0;
  u64 found_idx = string.size;
  for (u64 i = start; i < string.size; i += 1)
  {
    if (i + substr.size <= string.size)
    {
      Str8 processed_substr = sub_str8(string, i, i + substr.size);
      if (str8_match(processed_substr, substr, 0))
      {
        found_idx = i;
        found     = 1;
        if (!(flags & MatchFlag_FindLast))
        {
          break;
        }
      }
    }
  }
  return found_idx;
}

Str8 str8_skip(Str8 str, u64 min) { return sub_str8(str, min, str.size); }
