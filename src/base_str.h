#pragma once
#include "types.h"

struct Str8
{
    u8 *data;
    u64 size;
};

struct Str16
{
    u16 *data;
    u64 size;
};

struct Str32
{
    u32 *data;
    u64 size;
};

struct Str8Node
{
    Str8Node *next;
    Str8 string;
};

struct Str8List
{
    Str8Node *first;
    Str8Node *last;
    u64 count;
    u64 capacity;
};

struct Str8Array
{
    Str8 *v;
    u64 count;
};
