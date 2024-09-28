#pragma once
#include "arena.h"
#include "ren_types.h"
#include "my_maths.h"
#include "texture.h"

class Shader;

constexpr u32 MAX_QUAD_COUNT  = 20000;
constexpr u32 MAX_VERT_COUNT  = MAX_QUAD_COUNT * 4;
constexpr u32 MAX_INDEX_COUNT = MAX_QUAD_COUNT * 6;
constexpr u8 MAX_TEXTURE_SLOT = 30;

enum shader_types
{
    SHADER_BASIC,
    SHADER_TEXTURE,
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

// PERF: maybe, just MAYBE I can do some macro programming to automatically make
// a static function with the implementation function instead of writing it two
// times. Maybe, I don't know if it would make it less readable or not.
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

    static void quad(v3 min, v3 max, color Color)
    {
        return Get().quad_Im(min.x, min.y, min.x + max.x, min.y + max.y, Color);
    }

    // CLEAN: Make a single function that takes a default variable instead.
    static void setBackgroundColorRGB(const color &);
    static void setbackgroundColorHSL(const hsl_color &);
    static void setBackgroundColor(const color &);
    static void Init(Arena *arena) { return Get().Init_Im(arena); }

    static void end() { return Get().end_Im(); }
    static void begin() { return Get().begin_Im(SHADER_BASIC); }
    static void add_shader(Shader *currentShader, shader_types types)
    {
        return Get().add_shader_Im(currentShader, types);
    }

    static void begin_texture_mode()
    {
        return Get().begin_texture_mode_Im(SHADER_TEXTURE);
    }
    static void end_texture_mode() { return Get().end_texture_mode_Im(); }
    static void quad_texture(f32 x0,
                             f32 y0,
                             f32 x1,
                             f32 y1,
                             color Color,
                             v4 uv,
                             Texture2D *texture)
    {
        return Get().quad_texture_Im(x0, y0, x1, y1, Color, uv, texture);
    }
    static void
    quad_texture(v3 min, v3 max, color Color, v4 uv, Texture2D *texture)
    {
        return Get().quad_texture_Im(min.x,
                                     min.y,
                                     min.x + max.x,
                                     min.y + max.y,
                                     Color,
                                     uv,
                                     texture);
    }

  private:
    void Init_Im(Arena *);
    void end_Im();
    void begin_Im(s32 ShaderType);
    void
        quad_Im(f32,
                f32,
                f32,
                f32,
                color); // note(sown): This is about points not width and height
    void quad_texture_Im(f32 x0,
                         f32 y0,
                         f32 x1,
                         f32 y1,
                         color Color,
                         v4 uv,
                         Texture2D *texture);
    void flush();
    void begin_texture_mode_Im(s32 ShaderType);
    void end_texture_mode_Im();
    void texture_flush();
    void put_vertex(Vertex *, v2 position, color Color, v2 uv = {0, 0});
    void put_vertex(Vertex *vert,
                    v2 position,
                    color Color,
                    f32 texture_index,
                    v2 uv);
    void add_shader_Im(Shader *currentShader, shader_types types);

  private:
    ren() {}
    static ren s_Instance;

    Vertex *vertex_list;
    u32 *index_list;
    u32 vert_arr_id;
    u32 vert_buf_id;
    u32 index_buf_id;
    s32 num_vertices;
    s32 num_indices;

    s32 current_vertex_per_primitive;
    s32 max_vertex_count;
    s32 max_index_count;

    s32 draw_call;

    s32 texture_samplers[MAX_TEXTURE_SLOT];
    Texture2D *textures[MAX_TEXTURE_SLOT];
    s32 texture_slot_index;
    mat4x4 m_Projection;

    ren_shaders shaderList;
};
