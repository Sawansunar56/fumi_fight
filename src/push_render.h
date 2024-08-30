#pragma once
#include "arena.h"
#include "ren_types.h"
#include "my_maths.h"

class Shader;

enum shader_types
{
    SHADER_BASIC,
    SHADER_MAX
};

struct ren_shaders
{
    // Array of pointers
    // You initialize shaders and then just reference the data inside of this.
    // The array part is so that you can reference the values contiguously with 
    // the shader_types enum. 
    Shader **list; 
    u32 count;
    u32 maximum;
};

class ren
{
  public:
    ren(const ren &) = delete;
    static ren &Get()
    {
        static ren s_Instance;
        return s_Instance;
    }

    static void quad(f32 x0, f32 y0, f32 x1, f32 y1, color Color)
    {
        return Get().quad_Im(x0, y0, x1, y1, Color);
    }

    static void Init(Arena *arena, i32 max_vertex_count)
    {
        return Get().Init_Im(arena, max_vertex_count);
    }

    static void end() { return Get().end_Im(); }
    static void begin() { return Get().begin_Im(); }
    static void add_shader(Shader *currentShader, shader_types types)
    {
        return Get().add_shader_Im(currentShader, types);
    }

  private:
    void Init_Im(Arena *, i32 max_vertex_count);
    void end_Im();
    void begin_Im();
    void quad_Im(f32, f32, f32, f32, color); // NOTE: This is about points not width and height
    void flush();
    void put_vertex(Vertex *, v2 position, color Color);
    void add_shader_Im(Shader *currentShader, shader_types types);

  private:
    ren() {}
    static ren s_Instance;
    Vertex *vertex_list;
    u32 vert_arr_id;
    u32 vert_buf_id;
    s32 num_vertices;
    s32 current_vertex_per_primitive;
    s32 max_vertex_count;

    ren_shaders shaderList;
};
