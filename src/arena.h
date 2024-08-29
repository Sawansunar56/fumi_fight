#pragma once
#include "types.h"
#include <cassert>
#include <cstdlib>

#define Kilobytes(Value) ((Value) * 1024LL)
#define Megabytes(Value) (Kilobytes(Value) * 1024LL)
#define Gigabytes(Value) (Megabytes(Value) * 1024LL)

typedef struct memory_arena
{
    size_t size;
    size_t used;
    u8 *base;
} memory_arena;

typedef memory_arena Arena;

// Use this if you want to Initialize another arena on top of this.
inline void InitArena(memory_arena *arena, size_t size, void *base)
{
    arena->size = size;
    arena->base = (u8 *)base;
    arena->used = 0;
}

inline void ArenaRelease(memory_arena *arena) { 
    // free(arena); 
    delete []arena;
}

inline memory_arena *ArenaAlloc(u32 size)
{
    memory_arena *mainArena = (memory_arena *)malloc(size);
    assert(mainArena);

    InitArena(mainArena,
              size - sizeof(memory_arena),
              (u8 *)mainArena + sizeof(memory_arena));
    return mainArena;
}

inline void *PushSize_(memory_arena *arena, size_t size)
{
    assert((arena->used + size) <= arena->size);
    void *Result = arena->base + arena->used;
    arena->used += size;

    return Result;
}

inline void PopSize_(memory_arena *arena, size_t amt)
{
    assert((arena->used - amt) < 0);
    arena->used -= amt;
}

inline void ArenaClear(memory_arena *arena)
{
    arena->used = 0;
}

#define PushStruct(Arena, type) (type *)PushSize_(Arena, sizeof(type))
#define PushArray(Arena, count, type)                                          \
    (type *)PushSize_(Arena, (count) * sizeof(type))
#define PushSize(Arena, size) PushSize_(Arena, size)

// NOTE: Be really mindful of this. I don't understand pop as accurately as possible
// and even in professional code, I don't see it being used as often as the other
// functions. Because well, you might reduce it to shit. Just creating a new arena
// for specific functionality and just clear it out for certain conditions instead
// of this pop, because I might accidently just remove a thing that got pushed.
#define PopStruct(Arena, type) PopSize_(Arena, sizeof(type))
#define PopSize(Arena, amt) PopSize_(Arena, amt)
#define PopArray(Arena, count, type) \
        PopSize_(Arena, (count) * sizeof(type))
