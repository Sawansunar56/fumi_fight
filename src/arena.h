#pragma once
#include "types.h"
#include <cassert>
#include <cstdlib>
#include <cstring>

#define Kilobytes(Value) ((Value) * 1024LL)
#define Megabytes(Value) (Kilobytes(Value) * 1024LL)
#define Gigabytes(Value) (Megabytes(Value) * 1024LL)
#define Terabytes(Value) (Gigabytes(Value) * 1024LL)

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

#define MemoryCopy(dst, src, size) memmove((dst), (src), (size))
#define MemorySet(dst, byte, size) memset((dst), (byte), (size))
#define MemoryCompare(a, b, size)  memcmp((a), (b), (size))
#define MemoryStrlen(ptr)          strlen(ptr)

#define MemoryCopyStruct(d, s)     MemoryCopy((d), (s), sizeof(*(d)))
#define MemoryCopyArray(d, s)      MemoryCopy((d), (s), sizeof(d))
#define MemoryCopyTyped(d, s, c)   MemoryCopy((d), (s), sizeof(*(d))*(c))

#define MemoryZero(s,z)            memset((s), 0, (z))
#define MemoryZeroStruct(s)        MemoryZero((s), sizeof(*(s)))
#define MemoryZeroArray(a)         MemoryZero((a), sizeof(a))
#define MemoryZeroTyped(m, c)      MemoryZero((m), sizeof(*(m))*(c))

#define MemoryMatch(a, b, z)      (MemoryCompare((a), (b), (z)) == 0)
#define MemoryMatchStruct(a, b)    MemoryMatch((a), (b), sizeof(*(a)))
#define MemoryMatchArray(a, b)     MemoryMatch((a), (b), sizeof(a))

#define MemoryRead(T,p,e)    ( ((p)+sizeof(T)<=(e))?(*(T*)(p)):(0) )
#define MemoryConsume(T,p,e) ( ((p)+sizeof(T)<=(e))?((p)+=sizeof(T),*(T*)((p)-sizeof(T))):((p)=(e),0) )


//- rjf: linked list macro helpers
#define CheckNil(nil,p) ((p) == 0 || (p) == nil)
#define SetNil(nil,p) ((p) = nil)

//- rjf: doubly-linked-lists
#define DLLInsert_NPZ(nil,f,l,p,n,next,prev) (CheckNil(nil,f) ? \
((f) = (l) = (n), SetNil(nil,(n)->next), SetNil(nil,(n)->prev)) :\
CheckNil(nil,p) ? \
((n)->next = (f), (f)->prev = (n), (f) = (n), SetNil(nil,(n)->prev)) :\
((p)==(l)) ? \
((l)->next = (n), (n)->prev = (l), (l) = (n), SetNil(nil, (n)->next)) :\
(((!CheckNil(nil,p) && CheckNil(nil,(p)->next)) ? (0) : ((p)->next->prev = (n))), ((n)->next = (p)->next), ((p)->next = (n)), ((n)->prev = (p))))
#define DLLPushBack_NPZ(nil,f,l,n,next,prev) DLLInsert_NPZ(nil,f,l,l,n,next,prev)
#define DLLPushFront_NPZ(nil,f,l,n,next,prev) DLLInsert_NPZ(nil,l,f,f,n,prev,next)
#define DLLRemove_NPZ(nil,f,l,n,next,prev) (((n) == (f) ? (f) = (n)->next : (0)),\
((n) == (l) ? (l) = (l)->prev : (0)),\
(CheckNil(nil,(n)->prev) ? (0) :\
((n)->prev->next = (n)->next)),\
(CheckNil(nil,(n)->next) ? (0) :\
((n)->next->prev = (n)->prev)))

//- rjf: singly-linked, doubly-headed lists (queues)
#define SLLQueuePush_NZ(nil,f,l,n,next) (CheckNil(nil,f)?\
((f)=(l)=(n),SetNil(nil,(n)->next)):\
((l)->next=(n),(l)=(n),SetNil(nil,(n)->next)))
#define SLLQueuePushFront_NZ(nil,f,l,n,next) (CheckNil(nil,f)?\
((f)=(l)=(n),SetNil(nil,(n)->next)):\
((n)->next=(f),(f)=(n)))
#define SLLQueuePop_NZ(nil,f,l,next) ((f)==(l)?\
(SetNil(nil,f),SetNil(nil,l)):\
((f)=(f)->next))

//- rjf: singly-linked, singly-headed lists (stacks)
#define SLLStackPush_N(f,n,next) ((n)->next=(f), (f)=(n))
#define SLLStackPop_N(f,next) ((f)=(f)->next)

//- rjf: doubly-linked-list helpers
#define DLLInsert_NP(f,l,p,n,next,prev) DLLInsert_NPZ(0,f,l,p,n,next,prev)
#define DLLPushBack_NP(f,l,n,next,prev) DLLPushBack_NPZ(0,f,l,n,next,prev)
#define DLLPushFront_NP(f,l,n,next,prev) DLLPushFront_NPZ(0,f,l,n,next,prev)
#define DLLRemove_NP(f,l,n,next,prev) DLLRemove_NPZ(0,f,l,n,next,prev)
#define DLLInsert(f,l,p,n) DLLInsert_NPZ(0,f,l,p,n,next,prev)
#define DLLPushBack(f,l,n) DLLPushBack_NPZ(0,f,l,n,next,prev)
#define DLLPushFront(f,l,n) DLLPushFront_NPZ(0,f,l,n,next,prev)
#define DLLRemove(f,l,n) DLLRemove_NPZ(0,f,l,n,next,prev)

//- rjf: singly-linked, doubly-headed list helpers
#define SLLQueuePush_N(f,l,n,next) SLLQueuePush_NZ(0,f,l,n,next)
#define SLLQueuePushFront_N(f,l,n,next) SLLQueuePushFront_NZ(0,f,l,n,next)
#define SLLQueuePop_N(f,l,next) SLLQueuePop_NZ(0,f,l,next)
#define SLLQueuePush(f,l,n) SLLQueuePush_NZ(0,f,l,n,next)
#define SLLQueuePushFront(f,l,n) SLLQueuePushFront_NZ(0,f,l,n,next)
#define SLLQueuePop(f,l) SLLQueuePop_NZ(0,f,l,next)

//- rjf: singly-linked, singly-headed list helpers
#define SLLStackPush(f,n) SLLStackPush_N(f,n,next)
#define SLLStackPop(f) SLLStackPop_N(f,next)
