#pragma once
#include "base_types.h"
#include "arena.h"

class ren
{
  public:
    static void flush();
    static void quad(f32, f32, f32, f32, Color);
    static void put_vertex(Vertex *, V2 position, Color color);
    static void end();

    /* Initializes vertex array into the arena */
    static void Init(Arena *);

  private:
    static Vertex *vertex_list;
    static u32 vert_arr_id;
    static u32 vert_buf_id;
    static s32 num_vertices;
    static s32 current_vertex_per_primitive;
};
